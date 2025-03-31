/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:05:52 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 19:05:53 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_cylinder.h"
#include "math/double/double.h"
#include <stdio.h>

static void	report_non_unit_axis(void)
{
	printf("cylinder_new: warning: cylinder axis vector is not normalized\n");
}

t_error	cylinder_new(t_cylinder_specs specs, t_cylinder *out)
{
	if (double_eq(vec3_length(specs.axis), 0.0))
		return (E_UNEXPECTED_NULL_VECTOR);
	if (!vec3_is_unit(specs.axis))
	{
		specs.axis = vec3_normalize(specs.axis);
		report_non_unit_axis();
	}
	if (specs.radius < 0.0)
		return (E_OUT_OF_RANGE);
	if (specs.height < 0.0)
		return (E_OUT_OF_RANGE);
	*out = (t_cylinder){.point = specs.point, .axis = specs.axis,
		.radius = specs.radius, .height = specs.height, .color = specs.color};
	return (NO_ERROR);
}
