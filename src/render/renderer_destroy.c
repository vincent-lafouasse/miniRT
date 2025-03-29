/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:04:04 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 21:04:05 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_renderer.h"
#include <mlx.h>
#include <stdlib.h>

static void	properly_destroy_mlx_display(void *display);

void	renderer_destroy(t_renderer *self)
{
	if (!self)
		return ;
	if (self->img)
		mlx_destroy_image(self->mlx, self->img);
	if (self->window)
		mlx_destroy_window(self->mlx, self->window);
	if (self->mlx)
		properly_destroy_mlx_display(self->mlx);
}

static void	properly_destroy_mlx_display(void *display)
{
	mlx_destroy_display(display);
	free(display);
}
