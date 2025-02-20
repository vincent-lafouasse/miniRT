#include "gtest/gtest.h"

extern "C"
{
#include "mlx.h"
#include "libft.h"
};

TEST(Dummy, Dummy)
{
    int dummy = ft_strlen("420");
    void* mlx = mlx_init();
    SUCCEED();
}
