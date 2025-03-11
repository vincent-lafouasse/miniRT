#include "gtest/gtest.h"

extern "C" {
#include "libft.h"
};

TEST(Dummy, Dummy) {
    int dummy = ft_strlen("420");
    (void)dummy;
    SUCCEED();
}
