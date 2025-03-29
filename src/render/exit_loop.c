/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:03:33 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 21:03:34 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_renderer.h"
#include <X11/X.h>
#include <mlx.h>

int		key_hook(int keycode, void *mlx);
int		exit_hook(void *mlx);

void	renderer_set_exit_loop_on_esc(t_renderer *self)
{
	mlx_key_hook(self->window, key_hook, self->mlx);
}

void	renderer_set_exit_loop_on_cross(t_renderer *self)
{
	mlx_hook(self->window, DestroyNotify, StructureNotifyMask, exit_hook,
		self->mlx);
}
