/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_array_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:03:44 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 19:03:45 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_hittable.h"
#include "./t_hittable_array.h"
#include "math/t_interval/t_interval.h"
#include "ray/t_ray.h"
#include <stdbool.h>
#include <stddef.h>

bool	hittable_array_hit(const t_hittable_array *self, t_interval range,
		t_ray ray, t_hit_record *rec_out)
{
	size_t			i;
	t_hit_record	current;
	bool			hit_something;
	t_hit_record	nearest;

	i = 0;
	hit_something = false;
	while (i < self->len)
	{
		if (object_hit(&self->data[i], range, ray, &current))
		{
			range.max = current.t;
			hit_something = true;
			nearest = current;
		}
		i++;
	}
	if (hit_something)
		*rec_out = nearest;
	return (hit_something);
}
