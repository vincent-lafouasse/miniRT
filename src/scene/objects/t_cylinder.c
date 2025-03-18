#include "./t_cylinder.h"

t_cylinder cylinder_new(t_point3 point, t_vec3 axis, double diameter, double height, t_rgb color)
{
	t_cylinder cylinder;

	cylinder = (t_cylinder){.point = point, .axis = axis, .diameter = diameter, .height = height, .color = color};
	return (cylinder);
}
