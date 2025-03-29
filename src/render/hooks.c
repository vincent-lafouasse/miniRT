/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:03:09 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 21:03:09 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <mlx.h>

int	key_hook(int keycode, void *mlx)
{
	if (keycode == XK_Escape)
		mlx_loop_end(mlx);
	return (0);
}

int	exit_hook(void *mlx)
{
	mlx_loop_end(mlx);
	return (0);
}
