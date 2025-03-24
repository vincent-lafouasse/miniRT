#include "./t_plane.h"

t_plane plane_new(t_point3 origin, t_vec3 normal, t_rgb color)
{
	t_plane plane;

	plane = (t_plane){.origin = origin, .normal = normal, .color = color};
	return (plane);
}
