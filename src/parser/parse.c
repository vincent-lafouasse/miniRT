#include "./t_element.h"

#include "error/t_error.h"

#include "parser/t_element_list.h"
#include "camera/t_camera.h"
#include "scene/t_scene.h"

#include "libft/ft_string.h"

static t_error parse_elements(const char *input, t_element_list **elements_out);
t_error match_element(const char *line, t_element *element_out);

t_error	parse(const char *input, t_camera *cam_out, t_scene *scene_out)
{
	t_error			err;
	t_element_list	*elements;

	elements = NULL;
	err = parse_elements(input, &elements);
	if (err != NO_ERROR)
		return (err);
	return (NO_ERROR);
}

static t_error parse_elements(const char *input, t_element_list **elements_out)
{
	size_t		i;
	char		**nonempty_lines;
	t_error		err;
	t_element	element;

	nonempty_lines = ft_split(input, '\n');
	if (!nonempty_lines)
		return (E_OOM);
	i = 0;
	while (nonempty_lines[i] != NULL)
	{
		err = match_element(nonempty_lines[i], &element);
		if (err == E_LINE_EMPTY) {
			i++;
			continue;
		} else if (err != NO_ERROR) {
			ft_split_destroy(nonempty_lines);
			el_clear(elements_out);
			return (err);
		}
		err = el_push_front(elements_out, element);
		if (err != NO_ERROR) {
			ft_split_destroy(nonempty_lines);
			el_clear(elements_out);
			return (err);
		}
		i++;
	}
	return (NO_ERROR);
}

t_error	u8_parse(const char *str, uint8_t *result_out);
t_error double_parse(const char *str, double *result_out);

t_error vec3_parse(const char *str, t_vec3 *result_out)
{
	char **components;
	t_error x_err;
	t_error y_err;
	t_error z_err;

	components = ft_split(str, ',');
	if (!components)
		return (E_OOM);
	if (ft_split_len(components) != 3)
		return (E_MALFORMATTED_VECTOR);
	x_err = double_parse(components[0], &result_out->x);
	y_err = double_parse(components[1], &result_out->y);
	z_err = double_parse(components[2], &result_out->z);
	ft_split_destroy(components);
	if (x_err != NO_ERROR)
		return (x_err);
	if (y_err != NO_ERROR)
		return (y_err);
	if (z_err != NO_ERROR)
		return (z_err);
	return (NO_ERROR);
}

t_error color_parse(const char *str, uint8_t result_out[3])
{
	char **bytes;
	t_error r_err;
	t_error g_err;
	t_error b_err;

	bytes = ft_split(str, ',');
	if (!bytes)
		return (E_OOM);
	if (ft_split_len(bytes) != 3)
		return (E_MALFORMATTED_COLOR);
	r_err = u8_parse(bytes[0], &result_out[0]);
	g_err = u8_parse(bytes[1], &result_out[1]);
	b_err = u8_parse(bytes[2], &result_out[2]);
	ft_split_destroy(bytes);
	if (r_err != NO_ERROR)
		return (r_err);
	if (g_err != NO_ERROR)
		return (g_err);
	if (b_err != NO_ERROR)
		return (b_err);
	return (NO_ERROR);
}

