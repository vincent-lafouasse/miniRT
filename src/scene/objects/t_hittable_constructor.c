/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hittable_constructor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:23:24 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 17:23:27 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cylinder/t_cylinder.h"
#include "./plane/t_plane.h"
#include "./sphere/t_sphere.h"
#include "./t_hittable.h"

t_error	hittable_sphere_new(t_point3 origin, t_rgb color, double radius,
		t_hittable *out)
{
	t_sphere	sphere;
	t_error		err;

	err = sphere_new(origin, color, radius, &sphere);
	if (err != NO_ERROR)
		return (err);
	*out = ((t_hittable){.type = HITTABLE_SPHERE, .sphere = sphere});
	return (NO_ERROR);
}

t_error	hittable_plane_new(t_point3 origin, t_vec3 normal, t_rgb color,
		t_hittable *out)
{
	t_plane	plane;
	t_error	err;

	err = plane_new(origin, normal, color, &plane);
	if (err != NO_ERROR)
		return (err);
	*out = ((t_hittable){.type = HITTABLE_PLANE, .plane = plane});
	return (NO_ERROR);
}

t_error	hittable_cylinder_new(t_point3 point, t_vec3 axis, double radius,
		double height, t_rgb color, t_hittable *out)
{
	t_cylinder	cylinder;
	t_error		err;

	err = cylinder_new(point, axis, radius, height, color, &cylinder);
	if (err != NO_ERROR)
		return (err);
	*out = ((t_hittable){.type = HITTABLE_CYLINDER, .cylinder = cylinder});
	return (NO_ERROR);
}

t_error	hittable_triangle_new(t_point3 a, t_point3 b, t_point3 c, t_rgb color,
		t_hittable *out)
{
	t_triangle	triangle;
	t_error		err;

	err = triangle_new(a, b, c, color, &triangle);
	if (err != NO_ERROR)
		return (err);
	*out = (t_hittable){.type = HITTABLE_TRIANGLE, .triangle = triangle};
	return (NO_ERROR);
}
