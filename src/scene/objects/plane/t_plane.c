/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:34:29 by poss              #+#    #+#             */
/*   Updated: 2025/03/29 19:34:30 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_plane.h"
#include "math/double/double.h"
#include <stdio.h>

static void	report_non_unit_normal(void)
{
	printf("plane_new: warning: plane normal vector is not normalized\n");
}

t_error	plane_new(t_point3 origin, t_vec3 normal, t_rgb color, t_plane *out)
{
	if (double_eq(vec3_length(normal), 0.0))
		return (E_UNEXPECTED_NULL_VECTOR);
	if (!vec3_is_unit(normal))
	{
		normal = vec3_normalize(normal);
		report_non_unit_normal();
	}
	*out = (t_plane){.origin = origin, .normal = normal, .color = color};
	return (NO_ERROR);
}
