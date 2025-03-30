/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:13:32 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:13:35 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shading.h"

t_rgb	diffuse_shading(t_hit_record hit, t_point_light light)
{
	t_vec3	hit_to_light;
	double	diffuse_weight;

	hit_to_light = vec3_sub(light.coordinates, hit.point);
	hit_to_light = vec3_normalize(hit_to_light);
	diffuse_weight = light.intensity * vec3_dot(hit.normal, hit_to_light);
	diffuse_weight = fmax(0.0, diffuse_weight);
	return (vec3_mul(diffuse_weight, object_color(hit.object)));
}

t_rgb	total_diffuse_shading(t_hit_record hit,
		const t_point_light_array *lights, const t_hittable_array *objects)
{
	size_t			i;
	t_rgb			col;
	t_point_light	current_light;

	i = 0;
	col = rgb_black();
	while (i < lights->len)
	{
		current_light = lights->data[i];
		if (!hit_is_in_shadow(hit, objects, current_light))
		{
			col = vec3_add(col, diffuse_shading(hit, current_light));
		}
		i++;
	}
	return (col);
}
