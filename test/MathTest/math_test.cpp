#include "gtest/gtest.h"

extern "C" {
#include "math/t_point3.h"
#include "math/t_tuple4.h"
#include "math/t_vec3.h"
};

TEST(Tuple, W1_means_point) {
    t_tuple4 a = tuple4_new(4.3, -4.2, 3.1, 1.0);

    ASSERT_DOUBLE_EQ(a.x, 4.3);
    ASSERT_DOUBLE_EQ(a.y, -4.2);
    ASSERT_DOUBLE_EQ(a.z, 3.1);
    ASSERT_DOUBLE_EQ(a.w, 1.0);

    ASSERT_FALSE(vec3_is_valid(a));
    ASSERT_TRUE(point_is_valid(a));
}

TEST(Tuple, W0_means_point) {
    t_tuple4 a = tuple4_new(4.3, -4.2, 3.1, 0.0);

    ASSERT_DOUBLE_EQ(a.x, 4.3);
    ASSERT_DOUBLE_EQ(a.y, -4.2);
    ASSERT_DOUBLE_EQ(a.z, 3.1);
    ASSERT_DOUBLE_EQ(a.w, 0.0);

    ASSERT_TRUE(vec3_is_valid(a));
    ASSERT_FALSE(point_is_valid(a));
}

TEST(Tuple, Points_have_W1) {
    t_point3 actual = point_new(4, -4, 3);
    t_tuple4 expected = tuple4_new(4, -4, 3, 1.0);

    ASSERT_EQ(tuple4_compare(actual, expected), 0);
}
