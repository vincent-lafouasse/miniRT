/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:28:26 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:28:29 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	vec3_add(t_vec3 self, t_vec3 other)
{
	return (vec3_new(self.x + other.x, self.y + other.y, self.z + other.z));
}

t_vec3	vec3_negate(t_vec3 self)
{
	return (vec3_new(-self.x, -self.y, -self.z));
}

t_vec3	vec3_sub(t_vec3 self, t_vec3 other)
{
	return (vec3_add(self, vec3_negate(other)));
}

t_vec3	vec3_mul(double k, t_vec3 self)
{
	return (vec3_new(k * self.x, k * self.y, k * self.z));
}

t_vec3	vec3_div(t_vec3 self, double k)
{
	if (k == 0.0)
	{
		return (vec3_bogus());
	}
	return (vec3_mul(1.0 / k, self));
}
