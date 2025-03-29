/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_eq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:30:05 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:30:17 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/double/double.h"
#include "t_vec3.h"

bool	vec3_eq(t_vec3 self, t_vec3 other)
{
	return (double_eq(self.x, other.x) && double_eq(self.y, other.y)
		&& double_eq(self.z, other.z));
}
