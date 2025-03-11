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
