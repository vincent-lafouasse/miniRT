#include <cmath>
#include <iostream>
#include "Vector.hpp"
#include "gtest/gtest.h"

extern "C" {
#include "camera/t_camera.h"
#include "error/t_error.h"
#include "math/t_vec3/t_vec3.h"
};

#define EXPECT_VEC3_EQ(a, b) \
    EXPECT_DOUBLE_EQ(a.x, b.x); \
    EXPECT_DOUBLE_EQ(a.y, b.y); \
    EXPECT_DOUBLE_EQ(a.z, b.z);

#define EXPECT_CAM_EQ(a, b) \
    EXPECT_VEC3_EQ(a.position, b.position); \
    EXPECT_VEC3_EQ(a.pixel00, b.pixel00); \
    EXPECT_VEC3_EQ(a.delta_u, b.delta_u); \
    EXPECT_VEC3_EQ(a.delta_v, b.delta_v); \
    EXPECT_EQ(a.screen_width, b.screen_width); \
    EXPECT_EQ(a.screen_height, b.screen_height);

[[maybe_unused]]
static void log_camera(t_camera c, const char* name);
[[maybe_unused]]
static void log_vector(t_vec3 v, const char* name);

static double rad_to_deg(double radians) {
    return radians * 180.0 / M_PI;
}

TEST(Camera, NegativeFovFails) {
    size_t h = 1;
    size_t w = 1;

    Vector origin = Vector::Origin();
    Vector orientation = -Vector::E_Z();

    double fov_deg = -1;

    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, E_OUT_OF_RANGE);
}

TEST(Camera, TooBigFovFails) {
    size_t h = 1;
    size_t w = 1;

    Vector origin = Vector::Origin();
    Vector orientation = -Vector::E_Z();

    double fov_deg = 420;

    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, E_OUT_OF_RANGE);
}

TEST(Camera, ZeroFovFails) {
    size_t h = 1;
    size_t w = 1;

    Vector origin = Vector::Origin();
    Vector orientation = -Vector::E_Z();

    double fov_deg = 0;

    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, E_OUT_OF_RANGE);
}

TEST(Camera, NullVectorAsDirectionFails) {
    size_t h = 1;
    size_t w = 1;

    Vector origin = Vector::Origin();
    Vector orientation = Vector(0, 0, 0);

    double fov_deg = 90;

    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, E_UNEXPECTED_NULL_VECTOR);
}

TEST(Camera, AlongOz_OneByOne) {
    size_t h = 1;
    size_t w = 1;

    double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);
    double viewport_h = 2.0;
    double viewport_w = 2.0 * aspect_ratio;

    Vector origin = Vector::Origin();
    Vector orientation = -Vector::E_Z();

    // tan fov/2 = width / 2*focal_length
    double target_focal_length = 1.0;
    double fov_rad = 2.0 * std::atan(0.5 * viewport_w / target_focal_length);
    double fov_deg = rad_to_deg(fov_rad);

    Vector expected_viewport_u = Vector::E_X() * viewport_w;
    Vector expected_viewport_v = -Vector::E_Y() * viewport_h;

    Vector expected_viewport_center = origin + orientation;
    Vector expected_pixel00 = expected_viewport_center;

    t_camera expected = (t_camera){
        .position = origin.get(),
        .pixel00 = expected_pixel00.get(),
        .delta_u = expected_viewport_u.get(),
        .delta_v = expected_viewport_v.get(),
        .screen_width = w,
        .screen_height = h,
    };
    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, NO_ERROR);

    EXPECT_CAM_EQ(expected, actual);
}

TEST(Camera, AlongOz_TwoByTwo) {
    size_t h = 2;
    size_t w = 2;

    double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);
    double viewport_h = 2.0;
    double viewport_w = 2.0 * aspect_ratio;

    Vector origin = Vector::Origin();
    Vector orientation = -Vector::E_Z();

    // tan fov/2 = width / 2*focal_length
    double target_focal_length = 1.0;
    double fov_rad = 2.0 * std::atan(0.5 * viewport_w / target_focal_length);
    double fov_deg = rad_to_deg(fov_rad);

    Vector expected_viewport_u = Vector::E_X() * viewport_w;
    Vector expected_viewport_v = -Vector::E_Y() * viewport_h;

    Vector expected_delta_u = expected_viewport_u / static_cast<double>(w);
    Vector expected_delta_v = expected_viewport_v / static_cast<double>(h);

    Vector expected_viewport_center = origin + orientation;
    Vector expected_viewport_top_left = expected_viewport_center - (expected_viewport_u + expected_viewport_v) * 0.5;
    Vector expected_pixel00 = expected_viewport_top_left + (expected_delta_u + expected_delta_v) * 0.5;

    t_camera expected = (t_camera){
        .position = origin.get(),
        .pixel00 = expected_pixel00.get(),
        .delta_u = expected_delta_u.get(),
        .delta_v = expected_delta_v.get(),
        .screen_width = w,
        .screen_height = h,
    };
    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, NO_ERROR);

    EXPECT_CAM_EQ(expected, actual);
}

TEST(Camera, AlongOx_SixteenByNine) {
    size_t w = 16;
    size_t h = 9;

    double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);
    double viewport_h = 2.0;
    double viewport_w = 2.0 * aspect_ratio;

    Vector origin = Vector::Origin();
    Vector orientation = Vector::E_X();

    // tan fov/2 = width / 2*focal_length
    double target_focal_length = 1.0;
    double fov_rad = 2.0 * std::atan(0.5 * viewport_w / target_focal_length);
    double fov_deg = rad_to_deg(fov_rad);

    Vector viewport_right = Vector::E_Z();
    Vector viewport_down = -Vector::E_Y();
    Vector expected_viewport_u = viewport_right * viewport_w;
    Vector expected_viewport_v = viewport_down * viewport_h;

    Vector expected_delta_u = expected_viewport_u / static_cast<double>(w);
    Vector expected_delta_v = expected_viewport_v / static_cast<double>(h);

    Vector expected_viewport_center = origin + orientation;
    Vector expected_viewport_top_left = expected_viewport_center - (expected_viewport_u + expected_viewport_v) * 0.5;
    Vector expected_pixel00 = expected_viewport_top_left + (expected_delta_u + expected_delta_v) * 0.5;

    t_camera expected = (t_camera){
        .position = origin.get(),
        .pixel00 = expected_pixel00.get(),
        .delta_u = expected_delta_u.get(),
        .delta_v = expected_delta_v.get(),
        .screen_width = w,
        .screen_height = h,
    };
    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, NO_ERROR);

    EXPECT_CAM_EQ(expected, actual);
}

TEST(Camera, OffFromOrigin) {
    size_t w = 16;
    size_t h = 9;

    double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);
    double viewport_h = 2.0;
    double viewport_w = 2.0 * aspect_ratio;

    Vector origin = Vector(69, 420, 13);
    Vector orientation = Vector::E_X();

    // tan fov/2 = width / 2*focal_length
    double target_focal_length = 1.0;
    double fov_rad = 2.0 * std::atan(0.5 * viewport_w / target_focal_length);
    double fov_deg = rad_to_deg(fov_rad);

    Vector viewport_right = Vector::E_Z();
    Vector viewport_down = -Vector::E_Y();
    Vector expected_viewport_u = viewport_right * viewport_w;
    Vector expected_viewport_v = viewport_down * viewport_h;

    Vector expected_delta_u = expected_viewport_u / static_cast<double>(w);
    Vector expected_delta_v = expected_viewport_v / static_cast<double>(h);

    Vector expected_viewport_center = origin + orientation;
    Vector expected_viewport_top_left = expected_viewport_center - (expected_viewport_u + expected_viewport_v) * 0.5;
    Vector expected_pixel00 = expected_viewport_top_left + (expected_delta_u + expected_delta_v) * 0.5;

    t_camera expected = (t_camera){
        .position = origin.get(),
        .pixel00 = expected_pixel00.get(),
        .delta_u = expected_delta_u.get(),
        .delta_v = expected_delta_v.get(),
        .screen_width = w,
        .screen_height = h,
    };
    t_camera_specs specs = (t_camera_specs){
        .position = origin.get(),
        .direction = orientation.get(),
        .fov_deg = fov_deg,
    };
    t_camera actual;
    t_error err = camera_new(specs, w, h, &actual);
    ASSERT_EQ(err, NO_ERROR);

    EXPECT_CAM_EQ(expected, actual);
}

[[maybe_unused]]
static void log_vector(t_vec3 v, const char* name) {
    std::cout << "\t" << name << ":\t";
    std::cout << "{{ .x = " << v.x << ", .y = " << v.y << ", .z = " << v.z << " }}";
    std::cout << std::endl;
}

[[maybe_unused]]
static void log_camera(t_camera c, const char* name) {
    std::cout << "Camera " << name << " {\n";

    log_vector(c.position, "Position");
    log_vector(c.pixel00, "Pixel00");
    log_vector(c.delta_u, "Delta u");
    log_vector(c.delta_v, "Delta v");

    std::cout << "\tScreen:\t\t";
    std::cout << "{{ .height = " << c.screen_height << ", .width = " << c.screen_width << " }}\n";

    std::cout << "}" << std::endl;
}
