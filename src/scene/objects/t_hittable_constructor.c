#include "./t_hittable.h"

#include "./sphere/t_sphere.h"
#include "./plane/t_plane.h"
#include "./cylinder/t_cylinder.h"

t_error	hittable_sphere_new(t_point3 origin, t_rgb color, double radius, t_hittable *out)
{
	t_sphere sphere;
	t_error err;

	err = sphere_new(origin, color, radius, &sphere);
	if (err != NO_ERROR)
		return (err);
	*out = ((t_hittable){.type = HITTABLE_SPHERE, .sphere = sphere});
	return (NO_ERROR);
}

t_error	hittable_plane_new(t_point3 origin, t_vec3 normal, t_rgb color, t_hittable *out)
{
	t_plane plane;
	t_error err;

	err = plane_new(origin, normal, color, &plane);
	if (err != NO_ERROR)
		return (err);
	*out = ((t_hittable){.type = HITTABLE_PLANE, .plane = plane});
	return (NO_ERROR);
}

t_error	hittable_cylinder_new(t_point3 point, t_vec3 axis, double radius, double height, t_rgb color, t_hittable *out)
{
	t_cylinder cylinder;
	t_error err;

	err = cylinder_new(point, axis, radius, height, color, &cylinder);
	if (err != NO_ERROR)
		return (err);
	*out = ((t_hittable){.type = HITTABLE_CYLINDER, .cylinder = cylinder});
	return (NO_ERROR);
}
