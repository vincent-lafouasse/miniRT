/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:02:13 by poss              #+#    #+#             */
/*   Updated: 2025/04/01 20:02:14 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_hittable.h"
#include "math/double/double.h"
#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"
#include <stddef.h>

struct	s_triangle_hit_ctx
{
	t_triangle	tr;
	t_ray		r;
	t_vec3		e1;
	t_vec3		e2;
	t_vec3		rce2;
	double		det;
};
typedef struct s_triangle_hit_ctx	t_triangle_hit_ctx;

static t_triangle_hit_ctx	construct_ctx(t_triangle tr, t_ray r)
{
	t_triangle_hit_ctx	ctx;

	ctx.tr = tr;
	ctx.r = r;
	ctx.e1 = vec3_sub(tr.b, tr.a);
	ctx.e2 = vec3_sub(tr.c, tr.a);
	ctx.rce2 = vec3_cross(r.direction, ctx.e2);
	ctx.det = vec3_dot(ctx.rce2, ctx.e1);
	return (ctx);
}

static bool	get_hit(const t_triangle_hit_ctx *ctx, double *t)
{
	double	inv_det;
	t_vec3	s;
	double	u;
	t_vec3	s_cross_e1;
	double	v;

	inv_det = 1.0 / ctx->det;
	s = vec3_sub(ctx->r.origin, ctx->tr.a);
	u = inv_det * vec3_dot(s, ctx->rce2);
	if ((u < 0.0 && fabs(u) > DOUBLE_EPSILON) || (u > 1 && fabs(u
				- 1) > DOUBLE_EPSILON))
	{
		return (false);
	}
	s_cross_e1 = vec3_cross(s, ctx->e1);
	v = inv_det * vec3_dot(ctx->r.direction, s_cross_e1);
	if ((v < 0.0 && fabs(v) > DOUBLE_EPSILON) || (u + v > 1 && fabs(u + v
				- 1) > DOUBLE_EPSILON))
	{
		return (false);
	}
	*t = inv_det * vec3_dot(ctx->e2, s_cross_e1);
	return (true);
}

bool	triangle_hit(t_triangle triangle, t_interval range, t_ray ray,
		t_hit_record *rec)
{
	t_triangle_hit_ctx	ctx;
	double				t;

	ctx = construct_ctx(triangle, ray);
	if (double_eq(0.0, ctx.det))
		return (false);
	if (!get_hit(&ctx, &t))
		return (false);
	if (!interval_contains(range, t))
		return (false);
	*rec = (t_hit_record){.t = t, .point = ray_at(ray, t),
		.normal = triangle.normal, .object = NULL};
	if (vec3_dot(ray.direction, triangle.normal) > 0.0)
		rec->normal = vec3_negate(rec->normal);
	return (true);
}
