#include "../t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"

bool double_eq(double, double);

bool triangle_hit(t_triangle triangle, t_interval range, t_ray ray, t_hit_record *rec) {
	return false;
}
