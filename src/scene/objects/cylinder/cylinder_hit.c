#include "../t_hittable.h"

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

/*
// infinite cylinder defined by a base point cb, a normalized axis ca and a radious cr
vec2 cylIntersect( in vec3 ro, in vec3 rd, in vec3 cb, in vec3 ca, float cr )
{
    vec3  oc = ro - cb;
    float card = dot(ca,rd);
    float caoc = dot(ca,oc);
    float a = 1.0 - card*card;
    float b = dot( oc, rd) - caoc*card;
    float c = dot( oc, oc) - caoc*caoc - cr*cr;
    float h = b*b - a*c;
    if( h<0.0 ) return vec2(-1.0); //no intersection
    h = sqrt(h);
    return vec2(-b-h,-b+h)/a;
}
*/
bool double_eq(double, double);

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
		*rec = (t_hit_record){0};
		return true;
	}

	if (interval_contains(range, t1)) {
		*rec = (t_hit_record){0};
		return true;
	}

	return false;
}

bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);

bool cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	return cylinder_shaft_hit(cylinder, range, ray, rec);
}
