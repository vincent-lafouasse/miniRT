/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:09:00 by poss              #+#    #+#             */
/*   Updated: 2025/02/19 22:23:06 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include <math.h>

// half of those could probably be inlined

t_vec3	vec3_new(double x, double y, double z)
{
	return ((t_vec3){.x = x, .y = y, .z = z});
}

t_vec3	vec3_scale(double scalar, t_vec3 vec)
{
	return (vec3_new(scalar * vec.x, scalar * vec.y, scalar * vec.z));
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (vec3_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

double	dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	cross_product(t_vec3 v1, t_vec3 v2)
{
	double	x;
	double	y;
	double	z;

	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.y;
	z = v1.x * v2.y - v1.y * v2.x;
	return (vec3_new(x, y, z));
}

double	vec3_magnitude(t_vec3 v)
{
	return (sqrt(dot_product(v, v)));
}

t_vec3	vec3_normalized(t_vec3 v)
{
	double	magnitude;

	magnitude = vec3_magnitude(v);
	if (magnitude == 0.0)
	{
		return (vec3_new(0, 0, 0));
	}
	return (vec3_scale(1.0 / magnitude, v));
}
