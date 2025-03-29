/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_bogus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:32:37 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 00:34:00 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include <math.h>

t_vec3	vec3_bogus(void)
{
	return (vec3_new(INFINITY, INFINITY, INFINITY));
}

bool	vec3_is_bogus(t_vec3 self)
{
	return (!(isfinite(self.x) && isfinite(self.y) && isfinite(self.z)));
}
