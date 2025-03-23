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

	A = cy.axis, BP = base_to_camera = (ray.o - cy.base), D = ray.direction
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

bool cylinder_shaft_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);
bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);

bool cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	return (false);
}
