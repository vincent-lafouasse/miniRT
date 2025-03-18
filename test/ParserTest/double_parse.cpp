#include "gtest/gtest.h"

#include <format>

extern "C" {
#include "error/t_error.h"
t_error double_parse(const char *str, double *result_out);
};

TEST(DoubleParse, OneDotZeroWorks) {
	const char *input = "1.0";

	double result;
	double expected = 1.0;

	t_error err = double_parse(input, &result);
	ASSERT_EQ(err, NO_ERROR) << std::format("received error from double_parse method: {}", error_repr(err));

	ASSERT_DOUBLE_EQ(result, expected);
}

TEST(DoubleParse, OneAsIntegerWorks) {
	const char *input = "1";

	double result;
	double expected = 1.0;

	t_error err = double_parse(input, &result);
	ASSERT_EQ(err, NO_ERROR) << std::format("received error from double_parse method: {}", error_repr(err));

	ASSERT_DOUBLE_EQ(result, expected);
}

TEST(DoubleParse, ZeroWithLongFractionalPartWorks) {
	const char *input = "0.9483958396398324";

	double result;
	double expected = 0.9483958396398324;

	t_error err = double_parse(input, &result);
	ASSERT_EQ(err, NO_ERROR) << std::format("received error from double_parse method: {}", error_repr(err));

	ASSERT_DOUBLE_EQ(result, expected);
}

TEST(DoubleParse, NegativeNumberWorks) {
	const char *input = "-1.25";

	double result;
	double expected = -1.25;

	t_error err = double_parse(input, &result);
	ASSERT_EQ(err, NO_ERROR) << std::format("received error from double_parse method: {}", error_repr(err));

	ASSERT_DOUBLE_EQ(result, expected);
}

/*
TEST(Parser, EmptyStringIsInvalidNumber) {
}
TEST(Parser, LeadingDotIsInvalidNumber) {
}
*/
