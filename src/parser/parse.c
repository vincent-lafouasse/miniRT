#include "./parse.h"

#include "./element/t_element.h"
#include "./element/t_element_list/t_element_list.h"
#include "./element/t_partitioned_elements.h"

#include "error/t_error.h"

#include "math/t_rgb/t_rgb.h"
#include "math/t_vec3/t_vec3.h"
#include "camera/t_camera.h"

#include "read/read_file.h"
#include "scene/lights/t_ambient_light.h"
#include "scene/t_scene.h"

#include "libft/ft_string.h"

#include <stdlib.h>

t_error partitioned_elements_validate(const t_partitioned_elements *p);

static t_error parse_elements(const char *input, t_partitioned_elements *out);
t_error match_element(const char *line, t_element *element_out);
t_error gather_camera_and_scene(t_partitioned_elements *p, t_camera_specs *cam_out, t_scene *scene_out);

t_error gather_objects(t_partitioned_elements *p, t_hittable_array **out);
t_error gather_point_lights(t_partitioned_elements *p, t_point_light_array **out);

bool	ends_in_dot_rt(const char *str);

t_error	parse_from_file(const char *filename, t_camera_specs *cam_out, t_scene *scene_out)
{
	char *contents;
	t_error err;

	if (!ends_in_dot_rt(filename))
		return (E_BAD_MAP_SUFFIX);
	err = read_file(filename, &contents);
	if (err != NO_ERROR)
		return (err);
	err = parse(contents, cam_out, scene_out);
	free(contents);
	return (err);
}

t_error	parse(const char *input, t_camera_specs *cam_out, t_scene *scene_out)
{
	t_error			err;
	t_partitioned_elements	elements;

	elements = (typeof(elements)){NULL, NULL, NULL, NULL};
	err = parse_elements(input, &elements);
	if (err != NO_ERROR)
		return (err);
	err = gather_camera_and_scene(&elements, cam_out, scene_out);
	partitioned_elements_clear(&elements);
	return (err);
}

t_error make_ambient_light(t_element_list *amb, t_ambient_light *out)
{
	t_ambient_light_element ambient;
	t_rgb color;
	double intensity;

	if (el_len(amb) > 1)
		return (E_MUST_HAVE_ONE_AMBIENT_LIGHT);
	if (!amb)
	{
		color = rgb_black();
		intensity = 0.0;
	}
	else
	{
		ambient = amb->element.ambient;
		color = rgb_from_bytes(ambient.color);
		intensity = ambient.lighting_ratio;
	}
	return ambient_light(intensity, color, out);
}

t_error gather_camera_and_scene(t_partitioned_elements *p, t_camera_specs *cam_out, t_scene *scene_out)
{
	t_camera_element camera;
	t_point_light_array *lights;
	t_hittable_array *objects;
	t_ambient_light amb_light;
	t_error err;

	if (el_len(p->cameras) != 1)
		return (E_MUST_HAVE_ONE_CAMERA);
	camera = p->cameras->element.camera;
	*cam_out = (t_camera_specs){.position = camera.coordinates, \
		.direction = camera.orientation, .fov_deg = (double)camera.fov};
	err = make_ambient_light(p->ambients, &amb_light);
	if (err != NO_ERROR)
		return (err);
	err = gather_point_lights(p, &lights);
	if (err != NO_ERROR)
		return (err);
	err = gather_objects(p, &objects);
	if (err != NO_ERROR)
		return (point_light_array_destroy(&lights), err);
	*scene_out = scene_new(amb_light, lights, objects);
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
		if (err == E_LINE_EMPTY)
		{
			i++;
			continue;
		}
		else if (err != NO_ERROR)
			return (ft_split_destroy(nonempty_lines), partitioned_elements_clear(out), err);
		err = partitioned_elements_push_front(out, element);
		if (err != NO_ERROR)
			return (ft_split_destroy(nonempty_lines), partitioned_elements_clear(out), err);
		i++;
	}
	return (ft_split_destroy(nonempty_lines), NO_ERROR);
}
