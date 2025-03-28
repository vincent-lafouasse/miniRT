#include "../t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "ray/t_ray.h"

#include <stdbool.h>

struct s_disk {
	t_point3 center;
	t_vec3 normal;
	double radius;
};
typedef struct s_disk t_disk;

void get_endcaps(t_cylinder cy, t_disk* cap1, t_disk* cap2)
{
	t_vec3 shift = vec3_mul(cy.height / 2, cy.axis);

	*cap1 = (t_disk){
		.center = vec3_add(cy.point, shift),
		.normal = cy.axis,
		.radius = cy.radius,
	};

	*cap2 = (t_disk){
		.center = vec3_sub(cy.point, shift),
		.normal = cy.axis,
		.radius = cy.radius,
	};
}

bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec) {
	t_disk cap1;
	t_disk cap2;
	get_endcaps(cylinder, &cap1, &cap2);
	return false;
}
