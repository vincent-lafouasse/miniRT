/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:58:35 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:58:35 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_camera.h"
#include "render/t_renderer.h"
#include "scene/t_scene.h"
#include <stdio.h>

t_rgb	camera_pixel_color(const t_camera *camera, const t_scene *scene, int x,
			int y);
t_rgb	camera_pixel_color_with_antialiasing(const t_camera *camera,
			const t_scene *scene, int x, int y);
t_rgb	camera_pixel_color_flat(const t_camera *camera, const t_scene *scene,
			int x, int y);

void	camera_render_scene(const t_camera *camera, const t_scene *scene,
		t_renderer *renderer)
{
	t_rgb	color;
	size_t	x;
	size_t	y;

	x = 0;
	while (x < renderer->width)
	{
		printf("%zu/%zu\n", x + 1, renderer->width);
		y = 0;
		while (y < renderer->height)
		{
			color = camera_pixel_color(camera, scene, x, y);
			renderer_put_pixel(renderer, x, y, rgb_to_bytes(color));
			y++;
		}
		x++;
	}
	renderer_flush_pixels(renderer);
	renderer_enter_loop(renderer);
}
