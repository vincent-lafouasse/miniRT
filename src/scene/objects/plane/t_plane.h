/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_plane.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:34:51 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 19:35:15 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PLANE_H
# define T_PLANE_H

# include "error/t_error.h"
# include "math/t_rgb/t_rgb.h"
# include "math/t_vec3/t_vec3.h"

struct	s_plane
{
	t_point3	origin;
	t_vec3		normal;
	t_rgb		color;
};
typedef struct s_plane	t_plane;

t_error		plane_new(t_point3 origin, t_vec3 normal, t_rgb color,
				t_plane *out);

#endif // T_PLANE_H
