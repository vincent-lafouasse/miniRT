#include "./t_element.h"

#include "error/t_error.h"

#include "math/t_vec3/t_vec3.h"
#include "parser/t_element_list.h"
#include "camera/t_camera.h"
#include "scene/t_scene.h"

#include "libft/ft_string.h"

typedef struct s_partitioned_elements {
	t_element_list *cameras;
	t_element_list *ambients;
	t_element_list *lights;
	t_element_list *primitives;
} t_partitioned_elements;

static t_error parse_elements(const char *input, t_partitioned_elements *out);
t_error match_element(const char *line, t_element *element_out);
t_error gather_camera_and_scene(t_partitioned_elements *elements, t_camera *cam_out, t_scene *scene_out);

t_error partitioned_elements_push_front(t_partitioned_elements *p, t_element element);
void partitioned_elements_clear(t_partitioned_elements *p);
t_error partitioned_elements_validate(const t_partitioned_elements *p);

t_error	parse(const char *input, t_camera *cam_out, t_scene *scene_out)
{
	t_error			err;
	t_partitioned_elements	elements;

	elements = (typeof(elements)){NULL, NULL, NULL, NULL};
	err = parse_elements(input, &elements);
	if (err != NO_ERROR)
		return (err);
	err = partitioned_elements_validate(&elements);
	if (err != NO_ERROR)
	{
		partitioned_elements_clear(&elements);
		return (err);
	}
	return (NO_ERROR);
}

t_error partitioned_elements_validate(const t_partitioned_elements *p)
{
	const t_element_list *primitives;

	if (el_len(&p->ambients) != 1)
		return (E_TOO_MANY_AMBIENT_LIGHTS);
	const t_ambient_light_element ambient = p->ambients->element.ambient;
	if (ambient.lighting_ratio < 0.0 || ambient.lighting_ratio > 1.0)
		return (E_OUT_OF_RANGE);

	if (el_len(&p->cameras) != 1)
		return (E_TOO_MANY_CAMERAS);
	const t_camera_element camera = p->cameras->element.camera;
	if (!vec3_is_unit(camera.orientation))
		return (E_VECTOR_NOT_NORMALIZED);
	if (camera.fov > 180)
		return (E_OUT_OF_RANGE);

	if (el_len(&p->lights) != 1)
		return (E_MULTIPLE_LIGHTS_UNSUPPORTED);
	const t_light_element light = p->lights->element.light;
	if (light.brightness_ratio < 0.0 || light.brightness_ratio > 1.0)
		return (E_OUT_OF_RANGE);

	primitives = p->primitives;
	while (primitives)
	{
		t_element element = primitives->element;
		if (element.kind == ELEM_SPHERE_PRIMITIVE) {
		} else if (element.kind == ELEM_PLANE_PRIMITIVE) {
			if (!vec3_is_unit(element.plane.normal))
				return (E_VECTOR_NOT_NORMALIZED);
		} else if (element.kind == ELEM_CYLINDER_PRIMITIVE) {
			if (!vec3_is_unit(element.cylinder.axis))
				return (E_VECTOR_NOT_NORMALIZED);
		}
		primitives = primitives->next;
	}

	return (NO_ERROR);
}

t_error gather_camera_and_scene(t_partitioned_elements *elements, t_camera *cam_out, t_scene *scene_out)
{
	return (NO_ERROR);
}

static t_error parse_elements(const char *input, t_partitioned_elements *out)
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
			partitioned_elements_clear(out);
			return (err);
		}
		err = partitioned_elements_push_front(out, element);
		if (err != NO_ERROR) {
			ft_split_destroy(nonempty_lines);
			partitioned_elements_clear(out);
			return (err);
		}
		i++;
	}
	return (NO_ERROR);
}

t_error partitioned_elements_push_front(t_partitioned_elements *p, t_element element) {
	t_element_kind kind;

	kind = element.kind;
	if (kind == ELEM_CAMERA)
		return el_push_front(&p->cameras, element);
	else if (kind == ELEM_AMBIENT_LIGHT)
		return el_push_front(&p->ambients, element);
	else if (kind == ELEM_LIGHT)
		return el_push_front(&p->lights, element);
	else if (kind == ELEM_SPHERE_PRIMITIVE || \
			kind == ELEM_PLANE_PRIMITIVE || \
			kind == ELEM_CYLINDER_PRIMITIVE)
		return el_push_front(&p->primitives, element);
	return (E_UNREACHABLE);
}

void partitioned_elements_clear(t_partitioned_elements *p) {
	el_clear(&p->cameras);
	el_clear(&p->ambients);
	el_clear(&p->lights);
	el_clear(&p->primitives);
}
