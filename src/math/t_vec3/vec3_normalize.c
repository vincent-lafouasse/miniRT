/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:31:11 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:31:12 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "../double/double.h"

#include <math.h>

double	vec3_length(t_vec3 self)
{
	return (sqrt(vec3_dot(self, self)));
}

t_vec3	vec3_normalize(t_vec3 self)
{
	double	length;

	length = vec3_length(self);
	if (length == 0.0)
	{
		return (vec3_new(0.0, 0.0, 0.0));
	}
	return (vec3_div(self, length));
}

bool	vec3_is_unit(t_vec3 self)
{
	return (double_eq(vec3_dot(self, self), 1.0));
}
