/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:05:38 by poss              #+#    #+#             */
/*   Updated: 2025/04/01 19:17:40 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_hittable.h"
#include "math/t_interval/t_interval.h"
#include "ray/t_ray.h"
#include <stdbool.h>

bool				cylinder_endcap_hit(t_cylinder cylinder, t_interval range,
						t_ray ray, t_hit_record *rec);
bool				cylinder_shaft_hit(t_cylinder cylinder, t_interval range,
						t_ray ray, t_hit_record *rec);

static t_hit_record	closest_hit(t_hit_record h1, t_hit_record h2)
{
	if (h1.t < h2.t)
		return (h1);
	else
		return (h2);
}

bool	cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray,
		t_hit_record *rec)
{
	bool			shaft_hit;
	bool			cap_hit;
	t_hit_record	shaft_hit_rec;
	t_hit_record	cap_hit_rec;

	shaft_hit = cylinder_shaft_hit(cylinder, range, ray, &shaft_hit_rec);
	cap_hit = cylinder_endcap_hit(cylinder, range, ray, &cap_hit_rec);
	if (shaft_hit && cap_hit)
	{
		*rec = closest_hit(shaft_hit_rec, cap_hit_rec);
		return (true);
	}
	else if (shaft_hit)
	{
		*rec = shaft_hit_rec;
		return (true);
	}
	else if (cap_hit)
	{
		*rec = cap_hit_rec;
		return (true);
	}
	return (false);
}
