#include <cmath>
#include "gtest/gtest.h"

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
    t_vec3 a = vec3_new(DBL_MAX * 0.7, DBL_MAX * 0.7, DBL_MAX * 0.7);
    t_vec3 b = vec3_new(DBL_MAX * 0.7, DBL_MAX * 0.7, DBL_MAX * 0.7);

    t_vec3 v = vec3_add(a, b);

    ASSERT_FALSE(vec3_is_bogus(a));
    ASSERT_FALSE(vec3_is_bogus(b));
    ASSERT_TRUE(vec3_is_bogus(v));
}

TEST(Vec, VecNegate) {
    t_vec3 v = vec3_new(1.0, 2.0, 3.0);

    t_vec3 expected = vec3_new(-1.0, -2.0, -3.0);
    t_vec3 actual = vec3_negate(v);

    ASSERT_FALSE(vec3_is_bogus(actual));
    ASSERT_DOUBLE_EQ(expected.x, actual.x);
    ASSERT_DOUBLE_EQ(expected.y, actual.y);
    ASSERT_DOUBLE_EQ(expected.z, actual.z);
}

TEST(Vec, VecSubtract) {
    t_vec3 a = vec3_new(1.0, 2.0, 3.0);
    t_vec3 b = vec3_new(4.0, 5.0, 6.0);

    t_vec3 expected = vec3_new(-3.0, -3.0, -3.0);
    t_vec3 actual = vec3_sub(a, b);

    ASSERT_FALSE(vec3_is_bogus(actual));
    ASSERT_DOUBLE_EQ(expected.x, actual.x);
    ASSERT_DOUBLE_EQ(expected.y, actual.y);
    ASSERT_DOUBLE_EQ(expected.z, actual.z);
}

TEST(Vec, VecSubtractHuge) {
    t_vec3 a = vec3_new(-DBL_MAX * 0.7, -DBL_MAX * 0.7, -DBL_MAX * 0.7);
    t_vec3 b = vec3_new(DBL_MAX * 0.7, DBL_MAX * 0.7, DBL_MAX * 0.7);

    t_vec3 v = vec3_sub(a, b);

    ASSERT_FALSE(vec3_is_bogus(a));
    ASSERT_FALSE(vec3_is_bogus(b));
    ASSERT_TRUE(vec3_is_bogus(v));
}
