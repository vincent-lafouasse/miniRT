/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:13:45 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:19:36 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H

# include "camera/t_camera.h"
# include "math/t_rgb/t_rgb.h"
# include "scene/objects/t_hittable_array/t_hittable_array.h"
# include "scene/t_scene.h"

struct	s_specular_shading_ctx
{
	t_ray					r;
	double					alpha;
	const t_hittable_array	*objects;
};
typedef struct s_specular_shading_ctx	t_specular_ctx;

t_rgb	ambient_shading(t_ambient_light light);
t_rgb	total_diffuse_shading(t_hit_record hit,
			const t_point_light_array *lights,
			const t_hittable_array *objects);
t_rgb	total_specular_shading(t_hit_record hit,
			t_point_light_array *lights,
			struct s_specular_shading_ctx ctx);

bool	hit_is_in_shadow(t_hit_record rec,
			const t_hittable_array *objects,
			t_point_light light);

#endif
