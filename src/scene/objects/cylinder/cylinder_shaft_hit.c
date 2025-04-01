/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shaft_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:47:40 by poss              #+#    #+#             */
/*   Updated: 2025/04/01 19:47:55 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_hittable.h"
#include "math/double/double.h"
#include "math/t_interval/t_interval.h"
#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"
#include <stdbool.h>

struct	s_shaft_ctx
{
	t_cylinder	cy;
	t_ray		r;
	t_vec3		rc;
	t_vec3		n;
	double		n_len;
	double		d;
};
typedef struct s_shaft_ctx	t_shaft_ctx;

static bool	construct_ctx(t_cylinder cy, t_ray r, t_shaft_ctx *ctx)
{
	ctx->cy = cy;
	ctx->r = r;
	ctx->rc = vec3_sub(r.origin, cy.point);
	ctx->n = vec3_cross(r.direction, cy.axis);
	ctx->n_len = vec3_length(ctx->n);
	if (double_eq(ctx->n_len, 0))
		return (false);
	ctx->n = vec3_div(ctx->n, ctx->n_len);
	ctx->d = fabs(vec3_dot(ctx->rc, ctx->n));
	if (ctx->d >= cy.radius)
		return (false);
	return (true);
}

struct	s_shaft_hits
{
	double	t0;
	double	t1;
};
typedef struct s_shaft_hits	t_shaft_hits;

static void	get_candidates(const t_shaft_ctx *ctx, t_shaft_hits *hits)
{
	t_vec3	o;
	double	t_midpoint;
	double	t_shift;
	double	t0;
	double	t1;

	o = vec3_cross(ctx->rc, ctx->cy.axis);
	t_midpoint = -vec3_dot(o, ctx->n) / ctx->n_len;
	o = vec3_cross(ctx->n, ctx->cy.axis);
	o = vec3_normalize(o);
	t_shift = fabs(sqrt(ctx->cy.radius * ctx->cy.radius - ctx->d * ctx->d)
			/ vec3_dot(ctx->r.direction, o));
	t0 = t_midpoint - t_shift;
	t1 = t_midpoint + t_shift;
	hits->t0 = t0;
	hits->t1 = t1;
}

bool	candidate_hit_is_valid(double t, t_interval range,
		const t_shaft_ctx *ctx, t_hit_record *hit)
{
	t_point3	p;
	double		h;
	t_point3	projection;
	t_vec3		normal;

	if (!interval_contains(range, t))
		return (false);
	p = ray_at(ctx->r, t);
	h = vec3_dot(ctx->cy.axis, vec3_sub(p, ctx->cy.point));
	projection = vec3_add(ctx->cy.point, vec3_mul(h, ctx->cy.axis));
	if (-ctx->cy.height / 2 > h || h > ctx->cy.height / 2)
		return (false);
	normal = vec3_sub(p, projection);
	*hit = (t_hit_record){.point = p, .t = t, .normal = vec3_normalize(normal)};
	if (vec3_dot(ctx->r.direction, hit->normal) > 0)
		hit->normal = vec3_negate(hit->normal);
	return (true);
}

bool	cylinder_shaft_hit(t_cylinder cylinder, t_interval range, t_ray ray,
		t_hit_record *rec)
{
	t_shaft_ctx		ctx;
	t_shaft_hits	candidates;

	if (!construct_ctx(cylinder, ray, &ctx))
		return (false);
	get_candidates(&ctx, &candidates);
	if (candidate_hit_is_valid(candidates.t0, range, &ctx, rec))
		return (true);
	if (candidate_hit_is_valid(candidates.t1, range, &ctx, rec))
		return (true);
	return (false);
}
