/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:22:16 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 17:23:47 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_hittable.h"
#include "math/t_rgb/t_rgb.h"
#include <stdbool.h>

t_rgb	object_color(const t_hittable *object)
{
	t_rgb	color;

	if (!object)
		return (rgb_black());
	if (object->type == HITTABLE_SPHERE)
		color = object->sphere.color;
	else if (object->type == HITTABLE_PLANE)
		color = object->plane.color;
	else if (object->type == HITTABLE_CYLINDER)
		color = object->cylinder.color;
	else if (object->type == HITTABLE_TRIANGLE)
		color = object->triangle.color;
	else
		color = rgb_black();
	return (color);
}
