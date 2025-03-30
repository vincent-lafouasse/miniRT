/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_constructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:10:10 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:12:48 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point_light.h"
#include "t_ambient_light.h"

t_error	point_light(t_point3 coordinates, double intensity,
		t_rgb color, t_point_light *out)
{
	if (intensity < 0.0 || intensity > 1.0)
		return (E_OUT_OF_RANGE);
	out->coordinates = coordinates;
	out->intensity = intensity;
	out->color = color;
	return (NO_ERROR);
}

t_error	ambient_light(double intensity, t_rgb color,
		t_ambient_light *out)
{
	if (intensity < 0.0 || intensity > 1.0)
		return (E_OUT_OF_RANGE);
	out->intensity = intensity;
	out->color = color;
	return (NO_ERROR);
}
