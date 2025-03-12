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
