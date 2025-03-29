/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:03:45 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 21:04:13 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_renderer.h"
#include <mlx.h>

void	renderer_put_pixel(t_renderer *self, size_t x, size_t y, uint32_t color)
{
	char	*dst;

	dst = self->addr + (y * self->line_length + x * (self->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	renderer_flush_pixels(t_renderer *renderer)
{
	mlx_put_image_to_window(renderer->mlx, renderer->window, renderer->img, 0,
		0);
}
