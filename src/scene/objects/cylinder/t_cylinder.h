/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:05:55 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 19:06:09 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CYLINDER_H
# define T_CYLINDER_H

# include "error/t_error.h"
# include "math/t_rgb/t_rgb.h"
# include "math/t_vec3/t_vec3.h"

struct	s_cylinder
{
	t_point3	point;
	t_vec3		axis;
	double		radius;
	double		height;
	t_rgb		color;
};
typedef struct s_cylinder	t_cylinder;

t_error		cylinder_new(t_point3 point, t_vec3 axis,
				double radius, double height, t_rgb color,
				t_cylinder *out);
// t_hit_record cylinder_hit(t_camera cam, t_ray ray);

#endif // T_CYLINDER_H
