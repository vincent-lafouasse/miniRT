/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:06:53 by poss              #+#    #+#             */
/*   Updated: 2025/02/19 22:16:04 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VEC3_H
# define T_VEC3_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

t_vec3	vec3_new(double x, double y, double z);
t_vec3	vec3_scale(double scalar, t_vec3 vec);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);

double	dot_product(t_vec3 v1, t_vec3 v2);
t_vec3	cross_product(t_vec3 v1, t_vec3 v2);

// calls sqrt so is relatively expensive
double	vec3_magnitude(t_vec3 v);
t_vec3	vec3_normalized(t_vec3 v);

#endif
