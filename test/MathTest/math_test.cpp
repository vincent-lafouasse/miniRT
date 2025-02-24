#include "gtest/gtest.h"

extern "C" {
#include "math/t_point3.h"
#include "math/t_tuple4.h"
#include "math/t_vec3.h"
};

TEST(Tuple, W1_means_point) {
    t_tuple4 a = tuple4_new(4.3, -4.2, 3.1, 1.0);

    ASSERT_EQ(a.x, 4.3);
    ASSERT_EQ(a.y, -4.2);
    ASSERT_EQ(a.z, 3.1);
    ASSERT_EQ(a.w, 1.0);

    ASSERT_FALSE(vec3_is_valid((t_vec3)a));
    ASSERT_TRUE(point_is_valid((t_point3)a));
}
