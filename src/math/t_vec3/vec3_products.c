/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_products.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:28:43 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:29:05 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

double	vec3_dot(t_vec3 self, t_vec3 other)
{
	return (self.x * other.x + self.y * other.y + self.z * other.z);
}

t_vec3	vec3_cross(t_vec3 self, t_vec3 other)
{
	return (vec3_new(self.y * other.z - self.z * other.y, self.z * other.x
			- self.x * other.z, self.x * other.y - self.y * other.x));
}
