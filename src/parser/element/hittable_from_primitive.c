/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_from_primitive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:27:23 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:27:23 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_element.h"
#include "error/t_error.h"
#include "scene/objects/cylinder/t_cylinder.h"
#include "scene/objects/plane/t_plane.h"
#include "scene/objects/sphere/t_sphere.h"
#include "scene/objects/t_hittable.h"
#include "scene/objects/triangle/t_triangle.h"

static t_error	sphere_from_primitive(t_sphere_element s, t_hittable *out);
static t_error	plane_from_primitive(t_plane_element p, t_hittable *out);
static t_error	cylinder_from_primitive(t_cylinder_element c, t_hittable *out);
static t_error	triangle_from_primitive(t_triangle_element t, t_hittable *out);

t_error	hittable_from_primitive(t_element element, t_hittable *hittable)
{
	t_error	err;

	if (element.kind == ELEM_SPHERE_PRIMITIVE)
		err = sphere_from_primitive(element.sphere, hittable);
	else if (element.kind == ELEM_PLANE_PRIMITIVE)
		err = plane_from_primitive(element.plane, hittable);
	else if (element.kind == ELEM_CYLINDER_PRIMITIVE)
		err = cylinder_from_primitive(element.cylinder, hittable);
	else if (element.kind == ELEM_TRIANGLE_PRIMITIVE)
		err = triangle_from_primitive(element.triangle, hittable);
	else
		return (E_UNREACHABLE);
	return (err);
}

static t_error	sphere_from_primitive(t_sphere_element s, t_hittable *out)
{
	t_sphere_specs	sp_specs;

	sp_specs = (t_sphere_specs){s.center, rgb_from_bytes(s.color), s.diameter
		/ 2.0};
	return (hittable_sphere_new(sp_specs, out));
}

static t_error	plane_from_primitive(t_plane_element p, t_hittable *out)
{
	t_plane_specs	pl_specs;

	pl_specs = (t_plane_specs){p.point, p.normal, rgb_from_bytes(p.color)};
	return (hittable_plane_new(pl_specs, out));
}

static t_error	cylinder_from_primitive(t_cylinder_element c, t_hittable *out)
{
	t_cylinder_specs	cy_specs;

	cy_specs = (t_cylinder_specs){c.point, c.axis, c.diameter / 2.0, c.height,
		rgb_from_bytes(c.color)};
	return (hittable_cylinder_new(cy_specs, out));
}

static t_error	triangle_from_primitive(t_triangle_element t, t_hittable *out)
{
	t_triangle_specs	tri_specs;

	tri_specs = (t_triangle_specs){t.a, t.b, t.c, rgb_from_bytes(t.color)};
	return (hittable_triangle_new(tri_specs, out));
}
