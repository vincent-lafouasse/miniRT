/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_is_in_the_shadow.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:13:41 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:13:42 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/double/double.h"
#include "shading.h"

bool	hit_is_in_shadow(t_hit_record rec, const t_hittable_array *objects,
		t_point_light light)
{
	t_vec3			hit_to_light;
	double			distance_to_light;
	t_vec3			hit_to_light_unit;
	t_hit_record	_;

	hit_to_light = vec3_sub(light.coordinates, rec.point);
	distance_to_light = vec3_length(hit_to_light);
	hit_to_light_unit = vec3_div(hit_to_light, distance_to_light);
	return (hittable_array_hit(objects, interval_new(1024 * distance_to_light
				* DOUBLE_EPSILON, distance_to_light),
			(t_ray){.origin = rec.point, .direction = hit_to_light_unit}, &_));
}
