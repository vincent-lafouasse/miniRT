#include "error/t_error.h"

#include "libft/ctype.h"
#include "libft/string.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static bool		is_valid_double(const char *str);
static double	whole_part(const char *str);
static double	fractional_part(const char *str);
static uint8_t	parse_digit(char ch);

t_error double_parse(const char *str, double *result_out)
{
	char *dot;
	double result;

	if (!is_valid_double(str))
		return (E_INVALID_NUMBER);
	result = whole_part(str);
	dot = ft_strchr(str, '.');
	if (dot)
		result += fractional_part(dot);
	*result_out = result;
	return (NO_ERROR);
}

static bool	is_valid_double(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
	{
		if (str[i] != '.')
			return (false);
		i++;
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] != '\0')
			return (false);
	}
	return (true);
}

static double	whole_part(const char *str)
{
	size_t	i;
	double	whole;
	bool	negate;

	i = 0;
	whole = 0.0;
	negate = (str[i] == '-');
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] != '.') {
		whole = (whole * 10.0) + (double)parse_digit(str[i]);
		i++;
	}
	if (negate)
		whole = -whole;
	return whole;
}

static double	fractional_part(const char *str)
{
	size_t	i;
	double	fractional;
	double	current_fraction;

	i = 1;
	fractional = 0.0;
	while (str[i] != '\0') {
		current_fraction = (double)parse_digit(str[i]) / (i * 10.0);
		fractional = fractional + current_fraction;
		i++;
	}
	return fractional;
}

static uint8_t	parse_digit(char ch)
{
	return (ch - '0');
}
