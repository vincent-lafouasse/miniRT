#include "./t_plane.h"

#include "./t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"

#include <stdbool.h>
#include <stddef.h>

/*
	intersection if 
	||cy.axis x (ray.o + t ray.d - cy.base)||^2 == r^2 (a1)
	and [h = cy.axis . (ray.o + t ray.d - cy.base) signed height], h must be in [0, cy.height] (a2)

	with:
	A = cy.axis
	BP = base_to_camera = (ray.o - cy.base)
	D = ray.direction

	=> ||A x (BP + tD)||^2 == r^2  (1)
	=> || t (AxD) + AxBP||^2 == r^2 (2)
	=> (t (AxD) + AxBP), t (AxD) + AxBP)) == r2 (3)
	=> t2 (AxD)^2 + t (AxD).(AxBP) + t (AxBP).(AxD) + (AxBP)2 - r2 == 0 (4)
	=> t2 (AxD)2 + 2t (AxD).(AxBP) + (AxBP)2 - r2 == 0 (5)

	with acd = AxD and acbp = AxBP

	a = acd^2
	b = 2 * acd.acbp
	c = acbp^2 - r^2

	if a solution t exists, it must also verify (a2):

	(A, tD + BP) \in [0, cy.h]
*/

bool cylinder_shaft_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	t_point3 cy_bottom = vec3_sub(cylinder.point, vec3_mul(cylinder.height / 2.0, cylinder.axis));
	t_vec3 nca = vec3_cross(ray.direction, cylinder.axis);
	t_vec3 bca = vec3_cross(cy_bottom, cylinder.axis);
	double bdnca = vec3_dot(cy_bottom, nca);

	double determinant = vec3_dot(nca, nca) * cylinder.radius * cylinder.radius - bdnca * bdnca;

	if (determinant <= 0.0)
		return false;

	double determinant_sqrt = sqrt(determinant);

	double t0 = (vec3_dot(nca, bca) - determinant_sqrt) / vec3_dot(nca, nca);
	double t1 = (vec3_dot(nca, bca) + determinant_sqrt) / vec3_dot(nca, nca);

	t_interval height_range = interval_new(0.0, cylinder.height);

	if (interval_contains(range, t0)) {
		t_point3 hit = ray_at(ray, t0);
		double h = vec3_dot(cylinder.axis, vec3_sub(hit, cy_bottom));
		if (interval_contains(height_range, h))
		{
			t_vec3 projection = vec3_mul(h, cylinder.axis);
			projection = vec3_add(projection, cy_bottom);
			t_vec3 normal = vec3_sub(hit, projection);
			normal = vec3_normalize(normal);
			if (vec3_dot(normal, ray.direction) > 0.0)
				normal = vec3_negate(normal);

			*rec = (t_hit_record){
				.point = hit,
				.t = t0,
				.normal = normal,
				.object = NULL,
			};
		}
	}

	// duplication
	if (interval_contains(range, t1)) {
		t_point3 hit = ray_at(ray, t1);
		double h = vec3_dot(cylinder.axis, vec3_sub(hit, cy_bottom));
		if (interval_contains(height_range, h))
		{
			t_vec3 projection = vec3_mul(h, cylinder.axis);
			projection = vec3_add(projection, cy_bottom);
			t_vec3 normal = vec3_sub(hit, projection);
			normal = vec3_normalize(normal);
			if (vec3_dot(normal, ray.direction) > 0.0)
				normal = vec3_negate(normal);

			*rec = (t_hit_record){
				.point = hit,
				.t = t1,
				.normal = normal,
				.object = NULL,
			};
		}
	}

	return false;
}

bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);

bool cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	return cylinder_shaft_hit(cylinder, range, ray, rec);
}
