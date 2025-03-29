/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:59:23 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 20:59:30 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_ray.h"

t_ray	ray_new(t_point3 origin, t_vec3 direction)
{
	return ((t_ray){origin, direction});
}

t_point3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_mul(t, ray.direction)));
}
