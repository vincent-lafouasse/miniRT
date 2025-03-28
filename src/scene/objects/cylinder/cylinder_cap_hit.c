#include "../t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "ray/t_ray.h"

#include <stdbool.h>

struct s_disk {
	t_point3 center;
	t_vec3 normal;
	double radius;
	t_rgb color;
};
typedef struct s_disk t_disk;

bool	plane_hit(t_plane plane, t_interval range, t_ray ray, t_hit_record *rec);

bool	disk_hit(t_disk disk, t_interval range, t_ray ray, t_hit_record *rec) {
	t_plane parent_plane = (t_plane){.origin=disk.center, .normal=disk.normal, .color=disk.color};
	t_hit_record record;

	if (!plane_hit(parent_plane, range, ray, &record))
		return false;
	
	t_vec3 op = vec3_sub(record.point, disk.center);
	if (vec3_dot(op, op) > disk.radius * disk.radius)
		return false;
	if (vec3_dot(ray.direction, record.normal) > 0.0)
		record.normal = vec3_negate(record.normal);
	*rec = record;
	return true;
}

void get_endcaps(t_cylinder cy, t_disk* cap1, t_disk* cap2)
{
	t_vec3 shift = vec3_mul(cy.height / 2, cy.axis);

	*cap1 = (t_disk){
		.center = vec3_add(cy.point, shift),
		.normal = cy.axis,
		.radius = cy.radius,
		.color = cy.color,
	};

	*cap2 = (t_disk){
		.center = vec3_sub(cy.point, shift),
		.normal = cy.axis,
		.radius = cy.radius,
		.color = cy.color,
	};
}

bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec) {
	t_disk cap1;
	t_disk cap2;
	get_endcaps(cylinder, &cap1, &cap2);

	t_hit_record rec1;
	t_hit_record rec2;
	bool hit1 = disk_hit(cap1, range, ray, &rec1);
	bool hit2 = disk_hit(cap2, range, ray, &rec2);

	if (hit1 && hit2) {
		if (rec2.t < rec1.t)
		{
			*rec = rec2;
			return true;
		}
		else
		{
			*rec = rec1;
			return true;
		}
	}
	else if (hit1)
	{
		*rec = rec2;
		return true;
	}
	else if (hit2)
	{
		*rec = rec1;
		return true;
	}

	return false;
}
