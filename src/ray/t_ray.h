/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:58:27 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 20:59:16 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
# define T_RAY_H

# include "math/t_vec3/t_vec3.h"

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}				t_ray;

t_ray		ray_new(t_point3 origin, t_vec3 direction);
t_point3	ray_at(t_ray ray, double t);

#endif
