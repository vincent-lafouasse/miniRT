#include "../t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "math/double/double.h"
#include "ray/t_ray.h"

#include <stdbool.h>

bool cylinder_shaft_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	t_vec3 rc = vec3_sub(ray.origin, cylinder.point);

	t_vec3 n = vec3_cross(ray.direction, cylinder.axis);
	double n_len = vec3_length(n);
	if (double_eq(n_len, 0))
		return false;
	n = vec3_div(n, n_len);

	// shortest distqnce
	double d = fabs(vec3_dot(rc, n));
	if (d >= cylinder.radius)
		return false;

	t_vec3 o = vec3_cross(rc, cylinder.axis);
	double t_midpoint = -vec3_dot(o, n) / n_len;

	o = vec3_cross(n, cylinder.axis);
	o = vec3_normalize(o);
	double t_shift = fabs(sqrt(cylinder.radius * cylinder.radius - d * d));

	double t0 = t_midpoint - t_shift;
	double t1 = t_midpoint + t_shift;

	if (interval_contains(range, t0)) {
		t_point3 p = ray_at(ray, t0);
		double h = vec3_dot(cylinder.axis, vec3_sub(p, cylinder.point));
		t_point3 projection = vec3_add(cylinder.point, vec3_mul(h, cylinder.axis));
		t_vec3 normal = vec3_sub(p, projection);
		if (-cylinder.height / 2 <= h && h <= cylinder.height / 2) {
			*rec = (t_hit_record){.point = p, .t = t0, .normal = vec3_normalize(normal)};
			if (vec3_dot(ray.direction, rec->normal) > 0)
				rec->normal = vec3_negate(rec->normal);
			return true;
		}
	}

	if (interval_contains(range, t1)) {
		t_point3 p = ray_at(ray, t1);
		double h = vec3_dot(cylinder.axis, vec3_sub(p, cylinder.point));
		t_point3 projection = vec3_add(cylinder.point, vec3_mul(h, cylinder.axis));
		t_vec3 normal = vec3_sub(p, projection);
		if (-cylinder.height / 2 <= h && h <= cylinder.height / 2) {
			*rec = (t_hit_record){.point = p, .t = t1, .normal = vec3_normalize(normal)};
			if (vec3_dot(ray.direction, rec->normal) > 0)
				rec->normal = vec3_negate(rec->normal);
			return true;
		}
	}

	return false;
}

bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);

bool cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	return cylinder_shaft_hit(cylinder, range, ray, rec);
}
