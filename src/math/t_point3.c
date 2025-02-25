#include "t_point3.h"

t_point3	point_new(double x, double y, double z)
{
	return (tuple4_new(x, y, z, 1.0));
}

bool	point_is_valid(t_point3 point)
{
	return (point.w == 1.0);
}
