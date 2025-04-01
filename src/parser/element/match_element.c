#include "./t_element.h"

#include "error/t_error.h"

#include "libft/string.h"
#include "libft/ft_string.h"

#include "bonus.h"

#include <stddef.h>

t_error match_ambient_light(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_camera(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_light(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_sphere(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_plane(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_cylinder(char *const *parts, size_t parts_len, t_element *element_out);
t_error match_triangle(char *const *parts, size_t parts_len, t_element *element_out);

static char ft_strcmp(const char *s1, const char *s2) {
	return ft_strncmp(s1, s2, ft_strlen(s1) + 1);
}

static bool line_is_commented_out(const char *line)
{
	return (*line == '#');
}

static t_error match_element_dispatch(char **parts, size_t parts_len, t_element *out);

t_error match_element(const char *line, t_element *element_out)
{
	char	**parts;
	size_t	parts_len;
	t_error	err;

	if (line_is_commented_out(line))
		return (E_LINE_EMPTY);
	parts = ft_split_charset(line, " \t\v\n\r\f");
	if (!parts)
		return (E_OOM);
	parts_len = ft_split_len(parts);
	if (parts_len == 0)
	{
		ft_split_destroy(parts);
		return (E_LINE_EMPTY);
	}
	err = match_element_dispatch(parts, parts_len, element_out);
	ft_split_destroy(parts);
	return (err);
}

static t_error match_element_dispatch(char **parts, size_t parts_len, t_element *out)
{
	t_error err;

	if (0 == ft_strcmp(parts[0], TAG_AMBIENT_LIGHT))
		err = match_ambient_light(parts, parts_len, out);
	else if (0 == ft_strcmp(parts[0], TAG_CAMERA))
		err = match_camera(parts, parts_len, out);
	else if (0 == ft_strcmp(parts[0], TAG_LIGHT))
		err = match_light(parts, parts_len, out);
	else if (0 == ft_strcmp(parts[0], TAG_SPHERE))
		err = match_sphere(parts, parts_len, out);
	else if (0 == ft_strcmp(parts[0], TAG_PLANE))
		err = match_plane(parts, parts_len, out);
	else if (0 == ft_strcmp(parts[0], TAG_CYLINDER))
		err = match_cylinder(parts, parts_len, out);
	else if (BONUS_MODE && 0 == ft_strcmp(parts[0], TAG_TRIANGLE))
		err = match_triangle(parts, parts_len, out);
	else
		err = E_UNKNOWN_ELEMENT;
	return (err);
}
