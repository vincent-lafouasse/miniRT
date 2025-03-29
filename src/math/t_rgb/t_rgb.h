/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_rgb.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:21:50 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:26:05 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RGB_H
# define T_RGB_H

# include "math/t_vec3/t_vec3.h"
# include <stdint.h>

typedef struct s_vec3	t_rgb;

t_rgb		rgb_from_bytes(const uint8_t color[3]);
t_rgb		rgb_from_elements(uint8_t r, uint8_t g, uint8_t b);
uint32_t	rgb_to_bytes(t_rgb self);

static inline t_rgb	rgb_white(void)
{
	return ((t_rgb){.x = 1.0, .y = 1.0, .z = 1.0});
}

static inline t_rgb	rgb_black(void)
{
	return ((t_rgb){.x = 0.0, .y = 0.0, .z = 0.0});
}

#endif
