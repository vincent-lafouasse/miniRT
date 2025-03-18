#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include "Vector.hpp"

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

    Vector origin = Vector::Origin();
    Vector orientation = -Vector::E_Z();

    // tan fov/2 = width / 2*focal_length
    double target_focal_length = 1.0;
    double fov_rad = 2.0 * std::atan(0.5 * static_cast<double>(w) / target_focal_length);
    double fov_deg = fov_rad * 180.0 / M_PI;

    Vector expected_viewport_u = Vector::E_X() * 2.0;
    Vector expected_viewport_v = -Vector::E_Y() * 2.0;

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
    t_camera actual = camera_new(origin.get(), orientation.get(), fov_deg, w, h);

    expect_camera_eq(expected, actual);

    log_camera(actual, "Actual");
    log_camera(expected, "Expected");
}

static void log_vector(t_vec3 v, const char* name) {
    std::cout << "\t" << name << ":\t"; 
    std::cout << "{ .x = " << v.x << ", .y = " << v.y << ", .z = " << v.z << "}\n"; 
}

static void log_camera(t_camera c, const char* name) {
    std::cout << "Camera " << name << " {\n";

    log_vector(c.position, "Position");
    log_vector(c.pixel00, "Pixel00");
    log_vector(c.delta_u, "Delta u");
    log_vector(c.delta_v, "Delta v");

    std::cout << "\tScreen:\t" << "w = " << c.screen_width << ", h = " << c.screen_height << "\n";

    std::cout << "}" << std::endl;
}
