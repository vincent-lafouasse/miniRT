#include "error/t_error.h"

#include "libft/ctype.h"

#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>

static bool		is_valid_u8(const char *word);
static bool		will_overflow(uint8_t num, uint8_t addend);
static uint8_t	parse_digit(char ch);

t_error	u8_parse(const char *str, uint8_t *result_out)
{
	size_t	i;

	i = 0;
	if (!is_valid_u8(str))
		return (E_INVALID_NUMBER);
	*result_out = 0;
	while (ft_isdigit(str[i]))
	{
		if (will_overflow(*result_out, parse_digit(str[i])))
			return (E_OUT_OF_RANGE);
		*result_out *= 10;
		*result_out += parse_digit(str[i]);
		i++;
	}
	return (0);
}

static bool	is_valid_u8(const char *word)
{
	size_t	i;

	i = 0;
	if (word[i] == '\0')
		return (false);
	while (ft_isdigit(word[i]))
		i++;
	if (word[i] != '\0')
		return (false);
	return (true);
}

static bool	will_overflow(uint8_t num, uint8_t addend)
{
	if (num > UINT8_MAX / 10)
		return (true);
	num *= 10;
	if (num > UINT8_MAX - addend)
		return (true);
	return (false);
}

static uint8_t	parse_digit(char ch)
{
	return (ch - '0');
}
