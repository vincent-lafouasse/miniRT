/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:43:07 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:20:34 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_hittable.h"
#include "./t_sphere.h"
#include "math/t_interval/t_interval.h"
#include <stddef.h>

struct	s_sph_hit_ctx
{
	double	a;
	double	b;
	double	c;
};
typedef struct s_sph_hit_ctx	t_sph_hit_ctx;

static t_sph_hit_ctx	compute(t_sphere sph, t_ray ray)
{
	t_vec3	o_c;
	double	a;
	double	b;
	double	c;

	o_c = vec3_sub(sph.origin, ray.origin);
	a = vec3_dot(ray.direction, ray.direction);
	b = -2.0 * vec3_dot(ray.direction, o_c);
	c = vec3_dot(o_c, o_c) - sph.radius * sph.radius;
	return ((t_sph_hit_ctx){.a = a, .b = b, .c = c});
}

static t_hit_record	construct_hit_record(double t, t_ray ray, t_sphere sph)
{
	t_vec3	hit;
	t_vec3	normal;

	hit = ray_at(ray, t);
	normal = vec3_normalize(vec3_sub(hit, sph.origin));
	if (vec3_dot(ray.direction, normal) > 0.0)
	{
		normal = vec3_negate(normal);
	}
	return ((t_hit_record){.point = hit, .t = t, .normal = normal,
		.object = NULL});
}

bool	sphere_hit(t_sphere sphere, t_interval range, t_ray ray,
		t_hit_record *rec)
{
	t_sph_hit_ctx	ctx;
	double			delta;
	double			x0;
	double			x1;

	ctx = compute(sphere, ray);
	delta = ctx.b * ctx.b - 4.0 * ctx.a * ctx.c;
	if (delta < 0.0)
		return (false);
	delta = sqrt(delta);
	x0 = (-ctx.b - delta) / (2.0 * ctx.a);
	x1 = (-ctx.b + delta) / (2.0 * ctx.a);
	if (interval_contains(range, x0))
	{
		*rec = construct_hit_record(x0, ray, sphere);
		return (true);
	}
	if (interval_contains(range, x1))
	{
		*rec = construct_hit_record(x1, ray, sphere);
		return (true);
	}
	return (false);
}
