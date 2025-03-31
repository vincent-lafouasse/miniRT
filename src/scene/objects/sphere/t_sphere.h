/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sphere.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:20:58 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:20:59 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SPHERE_H
# define T_SPHERE_H

# include "error/t_error.h"
# include "math/t_rgb/t_rgb.h"
# include "math/t_vec3/t_vec3.h"

struct	s_sphere
{
	t_point3					origin;
	t_rgb						color;
	double						radius;
};
typedef struct s_sphere			t_sphere;

struct	s_sphere_specs
{
	t_point3					origin;
	t_rgb						color;
	double						radius;
};
typedef struct s_sphere_specs	t_sphere_specs;

t_error	sphere_new(t_sphere_specs specs, t_sphere *out);
// t_hit_record sphere_hit(t_camera cam, t_ray ray);

#endif // T_SPHERE_H
