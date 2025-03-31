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

t_error	cylinder_new(t_point3 point, t_vec3 axis, double radius, double height,
		t_rgb color, t_cylinder *out)
{
	if (double_eq(vec3_length(axis), 0.0))
		return (E_UNEXPECTED_NULL_VECTOR);
	if (!vec3_is_unit(axis))
	{
		axis = vec3_normalize(axis);
		report_non_unit_axis();
	}
	if (radius < 0.0)
		return (E_OUT_OF_RANGE);
	if (height < 0.0)
		return (E_OUT_OF_RANGE);
	*out = (t_cylinder){.point = point, .axis = axis, .radius = radius,
		.height = height, .color = color};
	return (NO_ERROR);
}
