/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:53:15 by poss              #+#    #+#             */
/*   Updated: 2025/03/27 19:56:21 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_hittable.h"
#include "./t_plane.h"
#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"
#include <stdbool.h>
#include <stddef.h>

static bool			parallel_ray_is_coplanar(t_plane plane, t_ray ray);
static bool			inside_of_plane(t_plane plane, t_ray ray,
						t_hit_record *out);
static t_hit_record	construct_hit_record(double t, t_ray ray, t_plane plane);

bool	plane_hit(t_plane plane, t_interval range, t_ray ray, t_hit_record *rec)
{
	t_vec3	camera_to_plane;
	double	t;

	if (vec3_dot(ray.direction, plane.normal) == 0.0)
	{
		if (parallel_ray_is_coplanar(plane, ray))
			return (inside_of_plane(plane, ray, rec));
		else
			return (false);
	}
	camera_to_plane = vec3_sub(plane.origin, ray.origin);
	t = vec3_dot(camera_to_plane, plane.normal) / vec3_dot(ray.direction,
			plane.normal);
	if (!interval_contains(range, t))
		return (false);
	*rec = construct_hit_record(t, ray, plane);
	return (true);
}

static t_hit_record	construct_hit_record(double t, t_ray ray, t_plane plane)
{
	t_point3	hit;

	hit = ray_at(ray, t);
	if (vec3_dot(ray.direction, plane.normal) > 0.0)
	{
		plane.normal = vec3_negate(plane.normal);
	}
	return ((t_hit_record){.point = hit, .t = t, .normal = plane.normal,
		.object = NULL});
}

static bool	parallel_ray_is_coplanar(t_plane plane, t_ray ray)
{
	const t_vec3	ray_to_plane = vec3_sub(ray.origin, plane.origin);

	return (vec3_dot(plane.normal, ray_to_plane) == 0.0);
}

static bool	inside_of_plane(t_plane plane, t_ray ray, t_hit_record *out)
{
	*out = (t_hit_record){
		.point = ray.origin,
		.t = 0.0,
		.normal = plane.normal,
	};
	return (true);
}
