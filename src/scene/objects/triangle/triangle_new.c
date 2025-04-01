/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:49:30 by poss              #+#    #+#             */
/*   Updated: 2025/04/01 19:53:46 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/double/double.h"
#include "t_triangle.h"

struct	s_edges
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	e3;
};
typedef struct s_edges	t_edges;

t_error	construct_edges(t_triangle_specs specs, t_edges *edges)
{
	edges->e1 = vec3_sub(specs.a, specs.b);
	edges->e2 = vec3_sub(specs.a, specs.c);
	edges->e3 = vec3_sub(specs.b, specs.c);
	if (double_eq(0.0, vec3_length(edges->e1)) || double_eq(0.0,
			vec3_length(edges->e2)) || double_eq(0.0, vec3_length(edges->e3)))
	{
		return (E_FLAT_TRIANGLE);
	}
	return (NO_ERROR);
}

t_error	triangle_new(t_triangle_specs specs, t_triangle *out)
{
	t_edges	edges;
	t_vec3	normal;
	double	normal_len;

	if (construct_edges(specs, &edges) != NO_ERROR)
		return (E_FLAT_TRIANGLE);
	normal = vec3_cross(edges.e1, edges.e2);
	normal_len = vec3_length(normal);
	if (double_eq(0.0, normal_len))
		return (E_FLAT_TRIANGLE);
	*out = (t_triangle){
		.a = specs.a,
		.b = specs.b,
		.c = specs.c,
		.normal = vec3_div(normal, normal_len),
		.color = specs.color,
	};
	return (NO_ERROR);
}
