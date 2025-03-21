#include "./t_plane.h"

#include "./t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"

#include <stdbool.h>

static bool parallel_ray_is_coplanar(t_plane plane, t_ray ray);
static bool inside_of_plane(t_plane plane, t_ray ray, t_hit_record *out);

bool plane_hit(t_plane plane, t_interval range, t_ray ray, t_hit_record *rec)
{
	if (vec3_dot(ray.direction, plane.normal) == 0.0)
	{
		if (parallel_ray_is_coplanar(plane, ray))
			return (inside_of_plane(plane, ray, rec));
		else
			return false;
	}
	/* ... */
	return (true);
}

static bool parallel_ray_is_coplanar(t_plane plane, t_ray ray) {
	const t_vec3 ray_to_plane = vec3_sub(ray.origin, plane.origin);

	return vec3_dot(plane.normal, ray_to_plane) == 0.0;
}

static bool inside_of_plane(t_plane plane, t_ray ray, t_hit_record *out)
{
	*out = (t_hit_record) {
		.point = ray.origin,
		.t = 0.0,
		.normal = plane.normal,
	};
	return (true);
}
