#include "./element/t_element.h"
#include "./element/t_element_list/t_element_list.h"
#include "./element/t_partitioned_elements.h"

#include "scene/lights/t_point_light.h"
#include "scene/lights/t_point_light_array/t_point_light_array.h"
#include "scene/objects/t_hittable.h"
#include "scene/objects/t_hittable_array/t_hittable_array.h"

#include "error/t_error.h"

t_error hittable_from_primitive(t_element element, t_hittable *hittable);

t_error gather_objects(t_partitioned_elements *p, t_hittable_array **out) {
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
			el_delone(&current);
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
			el_delone(&current);
			return (err);
		}
		point_light_array_push(lights, pt_light);
		el_delone(&current);
	}
	*out = lights;
	return (NO_ERROR);
}
