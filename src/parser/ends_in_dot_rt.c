#include "libft/string.h"
#include <stdbool.h>
#include <stddef.h>

bool ends_in_dot_rt(const char *str)
{
	size_t len;

	len = ft_strlen(str);
	return (len >= 3 && ft_strncmp(&str[len-3], ".rt", 3) == 0);
}
