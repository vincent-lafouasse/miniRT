#include <cmath>
#include <format>
#include <iostream>
#include "Vector.hpp"
#include "gtest/gtest.h"

extern "C" {
#include "camera/t_camera.h"
#include "math/t_vec3/t_vec3.h"
};

static void expect_camera_eq(t_camera expected, t_camera actual) {
    EXPECT_DOUBLE_EQ(expected.position.x, actual.position.x);
    EXPECT_DOUBLE_EQ(expected.position.y, actual.position.y);
    EXPECT_DOUBLE_EQ(expected.position.z, actual.position.z);

    EXPECT_DOUBLE_EQ(expected.pixel00.x, actual.pixel00.x);
    EXPECT_DOUBLE_EQ(expected.pixel00.y, actual.pixel00.y);
    EXPECT_DOUBLE_EQ(expected.pixel00.z, actual.pixel00.z);

    EXPECT_DOUBLE_EQ(expected.delta_u.x, actual.delta_u.x);
    EXPECT_DOUBLE_EQ(expected.delta_u.y, actual.delta_u.y);
    EXPECT_DOUBLE_EQ(expected.delta_u.z, actual.delta_u.z);

    EXPECT_DOUBLE_EQ(expected.delta_v.x, actual.delta_v.x);
    EXPECT_DOUBLE_EQ(expected.delta_v.y, actual.delta_v.y);
    EXPECT_DOUBLE_EQ(expected.delta_v.z, actual.delta_v.z);

    EXPECT_EQ(expected.screen_height, actual.screen_height);
    EXPECT_EQ(expected.screen_width, actual.screen_width);
}

static void log_camera(t_camera c, const char* name);

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
    double fov_deg = fov_rad * 180.0 / M_PI;

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
    t_camera actual = camera_new(specs, w, h);

    expect_camera_eq(expected, actual);

    log_camera(actual, "Actual");
    log_camera(expected, "Expected");
}

static void log_vector(t_vec3 v, const char* name) {
    std::cout << std::format("\t{}:\t", name);
    std::cout << std::format("{{ .x = {}, .y = {}, .z = {} }}", v.x, v.y, v.z);
    std::cout << std::endl;
}

static void log_camera(t_camera c, const char* name) {
    std::cout << "Camera " << name << " {\n";

    log_vector(c.position, "Position");
    log_vector(c.pixel00, "Pixel00");
    log_vector(c.delta_u, "Delta u");
    log_vector(c.delta_v, "Delta v");

    std::cout << "\tScreen:\t\t";
    std::cout << std::format("{{ .height = {}, .width = {} }}\n",
                             c.screen_height, c.screen_width);

    std::cout << "}" << std::endl;
}
