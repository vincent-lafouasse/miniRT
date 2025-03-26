#include "../t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"

bool double_eq(double, double);

bool triangle_hit(t_triangle triangle, t_interval range, t_ray ray, t_hit_record *rec) {
	t_vec3 edge1 = vec3_sub(triangle.a, triangle.b);
	t_vec3 edge2 = vec3_sub(triangle.a, triangle.c);
	t_vec3 ray_cross_e2 = vec3_cross(ray.direction, edge2);
	double det = vec3_dot(ray_cross_e2, edge1);
	if (double_eq(0.0, det))
		return false; // parallel
	return false;
}
