/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_convertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:21:47 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:26:43 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_rgb.h"

t_rgb	rgb_from_bytes(const uint8_t color[3])
{
	return (rgb_from_elements(color[0], color[1], color[2]));
}

t_rgb	rgb_from_elements(uint8_t r, uint8_t g, uint8_t b)
{
	double	r_double;
	double	g_double;
	double	b_double;

	r_double = (double)r / 256.0;
	g_double = (double)g / 256.0;
	b_double = (double)b / 256.0;
	return (vec3_new(r_double, g_double, b_double));
}

static uint8_t	clamp_and_cast_float(double value)
{
	if (value >= 255.0)
	{
		return (255);
	}
	else if (value < 0.0)
	{
		return (0);
	}
	return ((uint8_t)value);
}

uint32_t	rgb_to_bytes(t_rgb self)
{
	return ((clamp_and_cast_float(self.x
				* 256.0) << 16) | (clamp_and_cast_float(self.y
				* 256.0) << 8) | clamp_and_cast_float(self.z * 256.0));
}
