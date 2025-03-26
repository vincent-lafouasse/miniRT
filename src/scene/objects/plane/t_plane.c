#include "./t_plane.h"

#include <stdio.h>

static void report_non_unit_normal(void)
{
	printf("plane_new: warning: plane normal vector is not normalized\n");
}

t_error plane_new(t_point3 origin, t_vec3 normal, t_rgb color, t_plane *out)
{
	if (vec3_length(normal) == 0.0) // double_eq
		return (E_UNEXPECTED_NULL_VECTOR);
	if (!vec3_is_unit(normal))
	{
		normal = vec3_normalize(normal);
		report_non_unit_normal();
	}
	*out = (t_plane){.origin = origin, .normal = normal, .color = color};
	return (NO_ERROR);
}
