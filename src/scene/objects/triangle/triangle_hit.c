#include "../t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "math/double/double.h"
#include "ray/t_ray.h"

#include <stddef.h>

bool triangle_hit(t_triangle triangle, t_interval range, t_ray ray, t_hit_record *rec) {
	t_vec3 edge1 = vec3_sub(triangle.a, triangle.b);
	t_vec3 edge2 = vec3_sub(triangle.a, triangle.c);
	t_vec3 ray_cross_e2 = vec3_cross(ray.direction, edge2);
	double det = vec3_dot(ray_cross_e2, edge1);
	if (double_eq(0.0, det))
		return false; // parallel
	
	double inv_det = 1.0 / det;
	t_vec3 s = vec3_sub(ray.origin, triangle.a);
	double u = inv_det * vec3_dot(s, ray_cross_e2);
	if ((
		u < 0.0 && fabs(u) > DOUBLE_EPSILON
	) || (
		u > 1 && fabs(u - 1) > DOUBLE_EPSILON
	)) {
		return false;
	}

	t_vec3 s_cross_e1 = vec3_cross(s, edge1);
	double v = inv_det * vec3_dot(ray.direction, s_cross_e1);
	if ((v < 0.0 && fabs(v) > DOUBLE_EPSILON) || (u + v > 1 && fabs(u + v - 1) > DOUBLE_EPSILON)) {
		return false;
	}

	double t = inv_det * vec3_dot(edge2, s_cross_e1);
	if (!interval_contains(range, t))
		return false;

	*rec = (t_hit_record) {
		.t = t,
		.point = ray_at(ray, t),
		.normal = triangle.normal,
		.object = NULL
	};
	if (vec3_dot(ray.direction, triangle.normal) > 0.0)
		rec->normal = vec3_negate(rec->normal);

	return true;
}
