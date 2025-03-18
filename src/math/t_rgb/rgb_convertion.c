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
	double r;
	double g;
	double b;

	r = (double)color[0] / 256.0;
	g = (double)color[1] / 256.0;
	b = (double)color[2] / 256.0;
	return vec3_new(r, g, b);
}
