#include "libft.h"
#include "unity.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void compare_splits(const char** expected, const char** actual)
{
    while (*expected && *actual)
    {
        compare_strings(*expected, *actual);
        expected++;
        actual++;
    }

    if (expected == NULL && actual == NULL)
    {
        TEST_PASS();
    }

    char error[1024];
    sprintf(error,
            "Error, expected \"%s\" was \"%s\"",
            *expected, *actual);
    TEST_FAIL_MESSAGE(error);
}

static void test_ft_split_charset(void)
{
    const char* input = "\ta\v\nb\n   c\n\t\v\rd   ";
    const char* expected[] = {"a", "b", "c", "d", NULL};
    char** actual = ft_split_charset(input, " \t\v\r\n");

    compare_splits(expected, (const char**)actual);
    ft_split_destroy(actual);
}

void run_test_ft_split_charset(void)
{
    printf("\n----- SplitCharset -----\n");
    RUN_TEST(test_ft_split_charset);
}
