#include "t_camera.h"
#include <float.h>
#include <math.h>

typedef struct s_dimension
{
	double	w;
	double	h;
}			t_dimension;

typedef struct s_viewport
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	delta_u;
	t_vec3	delta_v;
}			t_viewport;

static t_viewport	construct_viewport(t_vec3 direction, t_dimension screen)
{
	t_vec3	viewport_up;
	t_vec3	viewport_right;
	t_vec3	viewport_down;
	t_vec3	u;
	t_vec3	v;

	// set "up" vaguely towards positive y
	// if colinear to e_y, set to e_x
	// direction really should be normalized for the colinearity check to work
	if (fabs(vec3_dot(direction, vec3_new(0.0, 1.0, 0.0))) - 1.0 < DBL_EPSILON)
	{
		viewport_up = vec3_new(1.0, 0.0, 0.0);
	}
	else
	{
		viewport_up = vec3_new(0.0, 1.0, 0.0);
	}

	// this yields an orthonormal base
	viewport_right = vec3_cross(direction, viewport_up);
	viewport_down = vec3_cross(direction, viewport_right);
	u = vec3_mul(2.0 * screen.w / screen.w, viewport_right);
	v = vec3_mul(2.0, viewport_down);
	return (t_viewport){
		.u = u,
		.v = v,
		.delta_u = vec3_mul(2.0 * screen.w / screen.h, viewport_right),
		.delta_v = vec3_mul(2.0, viewport_down),
	};
}

static t_vec3	compute_pixel00(t_point3 camera_position, t_vec3 direction,
		double fov_deg, t_viewport vp)
{
	double		fov_radians;
	double		focal_length;
	t_point3	viewport_center;
	t_point3	viewport_top_left;

	fov_radians = M_PI * fov_deg / 180.0;
	focal_length = 0.5 * vec3_length(vp.u) / tan(fov_radians / 2.0);
	viewport_center = vec3_add(camera_position, vec3_mul(focal_length,
				direction));
	viewport_top_left = vec3_sub(viewport_center, vec3_mul(0.5, vec3_add(vp.u,
					vp.v)));
	return (vec3_add(viewport_top_left, vec3_mul(0.5, vec3_add(vp.delta_u,
					vp.delta_v))));
}

t_camera	camera_new(t_camera_specs specs,
		size_t screen_width, size_t screen_height)
{
	t_viewport	vp;
	t_vec3		pixel00;

	vp = construct_viewport(specs.direction, (t_dimension){.w = screen_width,
			.h = screen_height});
	pixel00 = compute_pixel00(specs.position, specs.direction, specs.fov_deg, vp);
	return (t_camera){
		.position = specs.position,
		.pixel00 = pixel00,
		.delta_u = vp.delta_u,
		.delta_v = vp.delta_v,
		.screen_width = screen_width,
		.screen_height = screen_height,
	};
}
