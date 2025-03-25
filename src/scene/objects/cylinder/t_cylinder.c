#include "./t_cylinder.h"

#include <stdio.h>

static void report_non_unit_axis(void)
{
	printf("cylinder_new: warning: cylinder axis vector is not normalized\n");
}

t_cylinder cylinder_new(t_point3 point, t_vec3 axis, double radius, double height, t_rgb color)
{
	t_cylinder cylinder;

	if (!vec3_is_unit(axis))
	{
		axis = vec3_normalize(axis);
		report_non_unit_axis();
	}
	cylinder = (t_cylinder){.point = point, .axis = axis, .radius = radius, .height = height, .color = color};
	return (cylinder);
}
