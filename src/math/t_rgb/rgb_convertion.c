/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_convertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:21:47 by poss              #+#    #+#             */
/*   Updated: 2025/03/18 21:24:34 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_rgb.h"

t_rgb	rgb_from_bytes(const uint8_t color[3])
{
	return rgb_from_elements(color[0], color[1], color[2]);
}

t_rgb	rgb_from_elements(uint8_t r, uint8_t g, uint8_t b)
{
	double r_double;
	double g_double;
	double b_double;

	r_double = (double)r / 256.0;
	g_double = (double)g / 256.0;
	b_double = (double)b / 256.0;
	return vec3_new(r_double, g_double, b_double);
}
