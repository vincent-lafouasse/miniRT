/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:18:02 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 17:18:04 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lights/t_point_light_array/t_point_light_array.h"
#include "./objects/t_hittable_array/t_hittable_array.h"
#include "t_scene.h"

t_scene	scene_new(t_ambient_light ambient_light,
		t_point_light_array *point_lights, t_hittable_array *objects)
{
	return ((t_scene){.ambient_light = ambient_light,
		.point_lights = point_lights, .objects = objects});
}

void	scene_destroy(t_scene *scene)
{
	point_light_array_destroy(&scene->point_lights);
	hittable_array_destroy(&scene->objects);
}
