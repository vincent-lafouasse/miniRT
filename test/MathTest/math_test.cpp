#include "gtest/gtest.h"
#include <cmath>

extern "C" {
#include "math/t_vec3/t_vec3.h"
};

TEST(Vec, VecNew) {
    t_vec3 v = vec3_new(1.0, 2.0, 3.0);

    ASSERT_EQ(v.x, 1.0);
    ASSERT_EQ(v.y, 2.0);
    ASSERT_EQ(v.z, 3.0);
}

TEST(Vec, VecAdd) {
    t_vec3 a = vec3_new(1.0, 2.0, 3.0);
    t_vec3 b = vec3_new(4.0, 5.0, 6.0);

    t_vec3 expected = vec3_new(5.0, 7.0, 9.0);
    t_vec3 actual = vec3_add(a, b);

    ASSERT_FALSE(vec3_is_bogus(actual));
    ASSERT_DOUBLE_EQ(expected.x, actual.x);
    ASSERT_DOUBLE_EQ(expected.y, actual.y);
    ASSERT_DOUBLE_EQ(expected.z, actual.z);
}

TEST(Vec, VecAddHuge) {
    t_vec3 a = vec3_new(HUGE_VAL / 0.7, HUGE_VAL / 0.7, HUGE_VAL / 0.7);
    t_vec3 b = vec3_new(HUGE_VAL / 0.7, HUGE_VAL / 0.7, HUGE_VAL / 0.7);

    t_vec3 v = vec3_add(a, b);

    ASSERT_TRUE(vec3_is_bogus(v));
}
