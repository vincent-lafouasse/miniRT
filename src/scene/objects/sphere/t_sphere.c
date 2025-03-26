#include "./t_sphere.h"

t_error sphere_new(t_point3 origin, t_rgb color, double radius, t_sphere *out)
{
	if (radius < 0.0)
		return (E_OUT_OF_RANGE);
	*out = (t_sphere){.origin = origin, .color = color, .radius = radius};
	return (NO_ERROR);
}
