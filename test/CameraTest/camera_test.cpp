#include "gtest/gtest.h"
#include <cmath>

extern "C" {
#include "camera/t_camera.h"
#include "math/t_vec3/t_vec3.h"
};

static void assert_vec_equality(t_vec3 expected, t_vec3 actual) {
    ASSERT_DOUBLE_EQ(expected.x, actual.x);
    ASSERT_DOUBLE_EQ(expected.y, actual.y);
    ASSERT_DOUBLE_EQ(expected.z, actual.z);
}

const t_point3 O = vec3_new(0.0, 0.0, 0.0);
const t_vec3 E_X = vec3_new(1.0, 0.0, 0.0);
const t_vec3 E_Y = vec3_new(0.0, 1.0, 0.0);
const t_vec3 E_Z = vec3_new(0.0, 0.0, 1.0);
const t_vec3 NEG_E_X = vec3_new(-1.0, 0.0, 0.0);
const t_vec3 NEG_E_Y = vec3_new(0.0, -1.0, 0.0);
const t_vec3 NEG_E_Z = vec3_new(0.0, 0.0, -1.0);

TEST(Camera, AlongOz_OneByOne) {
    size_t h = 1;
    size_t w = 1;

    t_point3 origin = O;
    t_vec3 orientation = vec3_negate(E_Z);

    // tan fov/2 = width / 2*focal_length
    double target_focal_length = 1.0;
    double fov_rad = 2.0 * std::atan(0.5 * static_cast<double>(w) / target_focal_length);
    double fov_deg = fov_rad * 180.0 / M_PI;

    t_vec3 expected_viewport_u = vec3_mul(2.0, E_X);
    t_vec3 expected_viewport_center = orientation;
}

