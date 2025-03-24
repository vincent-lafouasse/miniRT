#include "./t_hittable.h"

#include "math/t_rgb/t_rgb.h"

#include <stdbool.h>
#include <stdlib.h>

t_rgb object_color(const t_hittable *object)
{
	t_rgb color;

	if (!object) // fallback logic, `object` is a valid reference to an initialized object
		return (rgb_black());

	if (object->type == HITTABLE_SPHERE)
		color = object->sphere.color;
	else if (object->type == HITTABLE_PLANE)
		color = object->plane.color;
	else if (object->type == HITTABLE_CYLINDER)
		color = object->cylinder.color;
	else
		abort(); // other shapes are unimplemented
	return (color);
}
