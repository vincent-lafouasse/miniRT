/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hittable.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:22:45 by poss              #+#    #+#             */
/*   Updated: 2025/03/31 17:23:17 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HITTABLE_H
# define T_HITTABLE_H

# include "./cylinder/t_cylinder.h"
# include "./plane/t_plane.h"
# include "./sphere/t_sphere.h"
# include "./triangle/t_triangle.h"
# include "error/t_error.h"
# include "math/t_interval/t_interval.h"
# include "math/t_rgb/t_rgb.h"
# include "ray/t_ray.h"

enum	e_hittable_type
{
	HITTABLE_SPHERE,
	HITTABLE_PLANE,
	HITTABLE_CYLINDER,
	HITTABLE_TRIANGLE,
};
typedef enum e_hittable_type	t_hittable_type;

typedef struct s_hittable		t_hittable;
struct	s_hittable
{
	t_hittable_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_triangle	triangle;
	};
};

t_error	hittable_sphere_new(t_point3 origin,
			t_rgb color, double radius,
			t_hittable *out);
t_error	hittable_plane_new(t_point3 origin,
			t_vec3 normal, t_rgb color,
			t_hittable *out);
t_error	hittable_cylinder_new(t_point3 point,
			t_vec3 axis, double radius, double height,
			t_rgb color, t_hittable *out);
t_error	hittable_triangle_new(t_point3 a, t_point3 b,
			t_point3 c, t_rgb color, t_hittable *out);

typedef struct s_hit_record		t_hit_record;
struct	s_hit_record
{
	t_point3			point;
	double				t;
	t_vec3				normal;
	const t_hittable	*object;
};

bool	object_hit(const t_hittable *object,
			t_interval range, t_ray ray,
			t_hit_record *rec_out);
t_rgb	object_color(const t_hittable *object);

#endif // T_HITTABLE_H
