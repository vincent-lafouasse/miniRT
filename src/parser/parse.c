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
#include "scene/lights/t_point_light.h"
#include "scene/lights/t_point_light_array/t_point_light_array.h"
#include "scene/objects/t_hittable.h"
#include "scene/objects/t_hittable_array/t_hittable_array.h"
#include "scene/t_scene.h"

#include "libft/ft_string.h"

#include <stdlib.h>

t_error partitioned_elements_validate(const t_partitioned_elements *p);

static t_error parse_elements(const char *input, t_partitioned_elements *out);
t_error match_element(const char *line, t_element *element_out);
t_error gather_camera_and_scene(t_partitioned_elements *p, t_camera_specs *cam_out, t_scene *scene_out);

t_error	parse_from_file(const char *filename, t_camera_specs *cam_out, t_scene *scene_out)
{
	char *contents;
	t_error err;

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

static t_error hittable_from_primitive(t_element element, t_hittable *hittable) {
	t_error err;
	t_sphere_element s;
	t_plane_element p;
	t_cylinder_element c;

	if (element.kind == ELEM_SPHERE_PRIMITIVE)
	{
		s = element.sphere;
		err = hittable_sphere_new(s.center, rgb_from_bytes(s.color), s.diameter / 2.0, hittable);
	}
	else if (element.kind == ELEM_PLANE_PRIMITIVE)
	{
		p = element.plane;
		err = hittable_plane_new(p.point, p.normal, rgb_from_bytes(p.color), hittable);
	}
	else if (element.kind == ELEM_CYLINDER_PRIMITIVE)
	{
		c = element.cylinder;
		err = hittable_cylinder_new(c.point, c.axis, c.diameter / 2.0, c.height, rgb_from_bytes(c.color), hittable);
	}
#ifndef MINIRT_RELEASE_BUILD  // do not include this in final build
	else
	{
		#include <assert.h>
		assert(!"unknown primitive");
	}
#endif
	return (err);
}

static t_error gather_objects(t_partitioned_elements *p, t_hittable_array **out) {
	t_error err;
	t_hittable_array	*objects;
	t_hittable			hittable;
	t_element_list		*current;

	objects = hittable_array_new(el_len(p->primitives));
	if (!objects)
		return (E_OOM);
	while (p->primitives) {
		current = el_pop_front_link(&p->primitives);
		err = hittable_from_primitive(current->element, &hittable);
		if (err != NO_ERROR)
		{
			hittable_array_destroy(&objects);
			return (err);
		}
		hittable_array_push(objects, hittable);
		el_delone(&current);
	}
	*out = objects;
	return (NO_ERROR);
}

t_error gather_point_lights(t_partitioned_elements *p, t_point_light_array **out)
{
	t_point_light_array	*lights;
	t_light_element		light;
	t_point_light		pt_light;
	t_error				err;
	t_element_list		*current;

	lights = point_light_array_new(el_len(p->lights));
	if (!lights)
		return (E_OOM);
	while (p->lights) {
		current = el_pop_front_link(&p->lights);
		light = current->element.light;
		err = point_light(light.coordinates, light.brightness_ratio, rgb_from_bytes(light.color), &pt_light);
		if (err != NO_ERROR)
		{
			point_light_array_destroy(&lights);
			return (err);
		}
		point_light_array_push(lights, pt_light);
		el_delone(&current);
	}
	*out = lights;
	return (NO_ERROR);
}

t_error gather_camera_and_scene(t_partitioned_elements *p, t_camera_specs *cam_out, t_scene *scene_out)
{
	if (el_len(p->ambients) != 1)
		return (E_TOO_MANY_AMBIENT_LIGHTS);

	if (el_len(p->cameras) != 1)
		return (E_TOO_MANY_CAMERAS);

	if (el_len(p->lights) == 0)
		return (E_NO_POINT_LIGHT);

	const t_camera_element camera = p->cameras->element.camera;
	const t_ambient_light_element ambient = p->ambients->element.ambient;
	t_point_light_array *lights;
	t_hittable_array *objects;
	t_error err;

	*cam_out = (t_camera_specs){.position = camera.coordinates, \
		.direction = camera.orientation, .fov_deg = (double)camera.fov};

	t_ambient_light amb_light;
	err = ambient_light(ambient.lighting_ratio, rgb_from_bytes(ambient.color), &amb_light);
	if (err != NO_ERROR)
		return (err);

	err = gather_point_lights(p, &lights);
	if (err != NO_ERROR)
		return (err);

	err = gather_objects(p, &objects);
	if (err != NO_ERROR)
		return (err);
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
	ft_split_destroy(nonempty_lines);
	return (NO_ERROR);
}
