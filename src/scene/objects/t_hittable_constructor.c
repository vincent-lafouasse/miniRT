#include "./t_hittable.h"

#include "./sphere/t_sphere.h"
#include "./plane/t_plane.h"
#include "./cylinder/t_cylinder.h"

t_hittable	hittable_sphere_new(t_sphere sphere)
{
	return ((t_hittable){.type = HITTABLE_SPHERE, .sphere = sphere});
}

t_hittable	hittable_plane_new(t_plane plane)
{
	return ((t_hittable){.type = HITTABLE_PLANE, .plane = plane});
}

t_hittable	hittable_cylinder_new(t_cylinder cylinder)
{
	return ((t_hittable){.type = HITTABLE_CYLINDER, .cylinder = cylinder});
}
