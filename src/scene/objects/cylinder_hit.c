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
	t_vec3 oc = vec3_sub(ray.origin, cylinder.point);
	double card = vec3_dot(cylinder.axis, ray.direction);
	double caoc = vec3_dot(cylinder.axis, oc);

	double a = 1.0 - card * card;
	double b = vec3_dot(oc, ray.direction) - caoc * card;
	double c = vec3_dot(oc, oc) - caoc * caoc - cylinder.radius * cylinder.radius;

	double d = b * b - a * c;

	if (d <= 0.0)
		return false;

	d = sqrt(d);

	double t0 = (-b - d) / a;
	double t1 = (-b + d) / a;

	if (interval_contains(range, t0)) {
		return true;
	}

	if (interval_contains(range, t1)) {
		return true;
	}

	return false;
}

bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);

bool cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	return cylinder_shaft_hit(cylinder, range, ray, rec);
}
