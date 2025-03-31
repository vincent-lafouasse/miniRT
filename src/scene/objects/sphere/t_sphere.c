/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:20:44 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:20:45 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_sphere.h"

t_error	sphere_new(t_sphere_specs specs, t_sphere *out)
{
	if (specs.radius < 0.0)
		return (E_OUT_OF_RANGE);
	*out = (t_sphere){.origin = specs.origin, .color = specs.color,
		.radius = specs.radius};
	return (NO_ERROR);
}
