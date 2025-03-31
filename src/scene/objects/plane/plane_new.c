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

t_error	plane_new(t_plane_specs specs, t_plane *out)
{
	if (double_eq(vec3_length(specs.normal), 0.0))
		return (E_UNEXPECTED_NULL_VECTOR);
	if (!vec3_is_unit(specs.normal))
	{
		specs.normal = vec3_normalize(specs.normal);
		report_non_unit_normal();
	}
	*out = (t_plane){.origin = specs.origin, .normal = specs.normal,
		.color = specs.color};
	return (NO_ERROR);
}
