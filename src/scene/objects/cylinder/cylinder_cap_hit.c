/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:23:21 by poss              #+#    #+#             */
/*   Updated: 2025/04/01 19:23:22 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_hittable.h"
#include "math/t_interval/t_interval.h"
#include "ray/t_ray.h"
#include <stdbool.h>

struct	s_disk
{
	t_point3	center;
	t_vec3		normal;
	double		radius;
	t_rgb		color;
};
typedef struct s_disk	t_disk;

struct s_caps
{
	t_disk	cap1;
	t_disk	cap2;
};
typedef struct s_caps	t_caps;

bool	plane_hit(t_plane plane, t_interval range, t_ray ray,
			t_hit_record *rec);

bool	disk_hit(t_disk disk, t_interval range, t_ray ray, t_hit_record *rec)
{
	t_plane			parent_plane;
	t_hit_record	record;
	t_vec3			op;

	parent_plane = (t_plane){.origin = disk.center, .normal = disk.normal,
		.color = disk.color};
	if (!plane_hit(parent_plane, range, ray, &record))
		return (false);
	op = vec3_sub(record.point, disk.center);
	if (vec3_dot(op, op) > disk.radius * disk.radius)
		return (false);
	if (vec3_dot(ray.direction, record.normal) > 0.0)
		record.normal = vec3_negate(record.normal);
	*rec = record;
	return (true);
}

void	get_endcaps(t_cylinder cy, t_caps *caps)
{
	t_vec3	shift;
	t_caps	out;

	shift = vec3_mul(cy.height / 2, cy.axis);
	out.cap1 = (t_disk){
		.center = vec3_add(cy.point, shift),
		.normal = cy.axis,
		.radius = cy.radius,
		.color = cy.color,
	};
	out.cap2 = (t_disk){
		.center = vec3_sub(cy.point, shift),
		.normal = cy.axis,
		.radius = cy.radius,
		.color = cy.color,
	};
	*caps = out;
}

static t_hit_record	closest_hit(t_hit_record h1, t_hit_record h2)
{
	if (h1.t < h2.t)
		return (h1);
	else
		return (h2);
}

bool	cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray,
		t_hit_record *rec)
{
	t_caps			caps;
	t_hit_record	rec1;
	t_hit_record	rec2;
	bool			hit1;
	bool			hit2;

	get_endcaps(cylinder, &caps);
	hit1 = disk_hit(caps.cap1, range, ray, &rec1);
	hit2 = disk_hit(caps.cap2, range, ray, &rec2);
	if (hit1 && hit2)
	{
		*rec = closest_hit(rec1, rec2);
		return (true);
	}
	else if (hit1)
	{
		*rec = rec1;
		return (true);
	}
	else if (hit2)
	{
		*rec = rec2;
		return (true);
	}
	return (false);
}
