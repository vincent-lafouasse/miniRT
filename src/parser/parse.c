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
	err = partitioned_elements_validate(&elements);
	if (err != NO_ERROR)
	{
		partitioned_elements_clear(&elements);
		return (err);
	}
	err = gather_camera_and_scene(&elements, cam_out, scene_out);
	partitioned_elements_clear(&elements);
	return (err);
}

t_error partitioned_elements_validate(const t_partitioned_elements *p)
{
	const t_element_list *primitives;

	if (el_len(p->ambients) != 1)
		return (E_TOO_MANY_AMBIENT_LIGHTS);
	const t_ambient_light_element ambient = p->ambients->element.ambient;
	if (ambient.lighting_ratio < 0.0 || ambient.lighting_ratio > 1.0)
		return (E_OUT_OF_RANGE);

	if (el_len(p->cameras) != 1)
		return (E_TOO_MANY_CAMERAS);
	const t_camera_element camera = p->cameras->element.camera;
	if (!vec3_is_unit(camera.orientation))
		return (E_VECTOR_NOT_NORMALIZED);
	if (camera.fov > 180)
		return (E_OUT_OF_RANGE);

	if (el_len(p->lights) != 1)
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

static t_hittable hittable_from_primitive(t_element element) {
	t_hittable hittable;
	t_sphere_element s;
	t_plane_element p;
	t_cylinder_element c;

	if (element.kind == ELEM_SPHERE_PRIMITIVE)
	{
		s = element.sphere;
		hittable = hittable_sphere_new(sphere_new(s.center, rgb_from_bytes(s.color), s.diameter / 2.0));
	}
	else if (element.kind == ELEM_PLANE_PRIMITIVE)
	{
		p = element.plane;
		hittable = hittable_plane_new(plane_new(p.point, p.normal, rgb_from_bytes(p.color)));
	}
	else if (element.kind == ELEM_CYLINDER_PRIMITIVE)
	{
		c = element.cylinder;
		hittable = hittable_cylinder_new(cylinder_new(c.point, c.axis, c.diameter / 2.0, c.height, rgb_from_bytes(c.color)));
	}
#ifndef MINIRT_RELEASE_BUILD  // do not include this in final build
	else
	{
		#include <assert.h>
		assert(!"unknown primitive");
	}
#endif
	return (hittable);
}

static t_hittable_array *gather_objects(t_partitioned_elements *p) {
	t_hittable_array	*objects;
	t_hittable			hittable;
	t_element_list		*current;

	objects = hittable_array_new(el_len(p->primitives));
	if (!objects)
		return (NULL);
	while (p->primitives) {
		current = el_pop_front_link(&p->primitives);
		hittable = hittable_from_primitive(current->element);
		hittable_array_push(objects, hittable);
		el_delone(&current);
	}
	return (objects);
}

t_error gather_camera_and_scene(t_partitioned_elements *p, t_camera_specs *cam_out, t_scene *scene_out)
{
	const t_camera_element camera = p->cameras->element.camera;
	const t_ambient_light_element ambient = p->ambients->element.ambient;
	const t_light_element light = p->lights->element.light;
	t_hittable_array *objects;

	*cam_out = (t_camera_specs){.position = camera.coordinates, \
		.direction = camera.orientation, .fov_deg = (double)camera.fov};
	t_ambient_light amb_light = ambient_light(ambient.lighting_ratio, rgb_from_bytes(ambient.color));
	t_point_light pt_light = point_light(light.coordinates, light.brightness_ratio, rgb_from_bytes(light.color));
	objects = gather_objects(p);
	if (!objects)
		return (E_OOM);
	*scene_out = scene_new(amb_light, pt_light, objects);
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
