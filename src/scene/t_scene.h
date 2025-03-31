/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:18:06 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 17:18:21 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SCENE_H
# define T_SCENE_H

# include "./lights/t_ambient_light.h"
# include "./lights/t_point_light.h"
# include "./lights/t_point_light_array/t_point_light_array.h"
# include "./objects/t_hittable_array/t_hittable_array.h"
# include "math/t_rgb/t_rgb.h"

struct	s_scene
{
	t_ambient_light		ambient_light;
	t_point_light_array	*point_lights;
	t_hittable_array	*objects;
};
typedef struct s_scene	t_scene;

t_scene	scene_new(t_ambient_light ambient_light,
			t_point_light_array *point_lights,
			t_hittable_array *objects);

t_rgb	scene_ray_color(const t_scene *scene, t_ray r);

void	scene_destroy(t_scene *scene);

#endif // T_SCENE_H
