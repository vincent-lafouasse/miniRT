#include "./t_plane.h"

#include "./t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"

#include <stdbool.h>
#include <stddef.h>

/*
	intersection if 
	||cy.axis x (ray.o + t ray.d - cy.base)||^2 == r^2
	and [h = cy.axis . (ray.o + t ray.d - cy.base) signed height], h must be in [0, cy.height]
*/

bool cylinder_shaft_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);
bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);

bool cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	return (false);
}
