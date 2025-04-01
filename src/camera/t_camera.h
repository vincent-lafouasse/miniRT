/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:36:16 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:36:35 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CAMERA_H
# define T_CAMERA_H

# include "error/t_error.h"
# include "math/t_rgb/t_rgb.h"
# include "math/t_vec3/t_vec3.h"
# include "render/t_renderer.h"
# include "scene/t_scene.h"
# include <stddef.h>

struct							s_camera
{
	t_point3					position;
	t_point3					pixel00;
	t_vec3						delta_u;
	t_vec3						delta_v;
	size_t						screen_width;
	size_t						screen_height;
};
typedef struct s_camera			t_camera;

struct							s_camera_specs
{
	t_point3					position;
	t_vec3						direction;
	double						fov_deg;
};
typedef struct s_camera_specs	t_camera_specs;

t_error							camera_new(t_camera_specs specs,
									size_t screen_width, size_t screen_height,
									t_camera *out);

void							camera_render_scene(const t_camera *camera,
									const t_scene *scene, t_renderer *renderer);

#endif // T_CAMERA_H
