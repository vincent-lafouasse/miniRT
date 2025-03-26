#include "./t_cylinder.h"

#include <stdio.h>

static void report_non_unit_axis(void)
{
	printf("cylinder_new: warning: cylinder axis vector is not normalized\n");
}

t_error cylinder_new(t_point3 point, t_vec3 axis, double radius, double height, t_rgb color, t_cylinder *out)
{
	if (vec3_length(axis) == 0.0) // double_eq
		return (E_UNEXPECTED_NULL_VECTOR);
	if (!vec3_is_unit(axis))
	{
		axis = vec3_normalize(axis);
		report_non_unit_axis();
	}
	if (radius < 0.0)
		return (E_OUT_OF_RANGE);
	if (height < 0.0)
		return (E_OUT_OF_RANGE);
	*out = (t_cylinder){.point = point, .axis = axis, .radius = radius, .height = height, .color = color};
	return (NO_ERROR);
}
