/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point_light.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:09:52 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:11:17 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_POINT_LIGHT_H
# define T_POINT_LIGHT_H

# include "error/t_error.h"
# include "math/t_rgb/t_rgb.h"
# include "math/t_vec3/t_vec3.h"

struct		s_point_light
{
	t_vec3	coordinates;
	double	intensity;
	t_rgb	color;
};
typedef struct s_point_light	t_point_light;

t_error	point_light(t_point3 coordinates, double intensity,
			t_rgb color, t_point_light *out);

#endif // T_POINT_LIGHT_H
