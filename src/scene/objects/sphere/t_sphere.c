#include "./t_sphere.h"

t_sphere sphere_new(t_point3 origin, t_rgb color, double radius)
{
	t_sphere sphere;

	sphere = (t_sphere){.origin = origin, .color = color, .radius = radius};
	return (sphere);
}
