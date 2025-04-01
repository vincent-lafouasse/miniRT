/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_triangle.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:48:39 by poss              #+#    #+#             */
/*   Updated: 2025/04/01 19:49:01 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TRIANGLE_H
# define T_TRIANGLE_H

# include "error/t_error.h"
# include "math/t_rgb/t_rgb.h"
# include "math/t_vec3/t_vec3.h"

struct	s_triangle
{
	t_point3	a;
	t_point3	b;
	t_point3	c;
	t_vec3		normal;
	t_rgb		color;
};
typedef struct s_triangle		t_triangle;

struct	s_triangle_specs
{
	t_point3	a;
	t_point3	b;
	t_point3	c;
	t_rgb		color;
};
typedef struct s_triangle_specs	t_triangle_specs;

t_error	triangle_new(t_triangle_specs specs,
			t_triangle *out);

#endif
