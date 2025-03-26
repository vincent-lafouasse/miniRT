#include "./t_sphere.h"

t_error sphere_new(t_point3 origin, t_rgb color, double radius, t_sphere *out)
{
	*out = (t_sphere){.origin = origin, .color = color, .radius = radius};
	return (NO_ERROR);
}
