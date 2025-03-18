#ifndef T_CAMERA_H
# define T_CAMERA_H

# include "math/t_vec3/t_vec3.h"
# include <stddef.h>

struct	s_camera
{
	t_point3	position;
	t_point3	pixel00;
	t_vec3		delta_u;
	t_vec3		delta_v;
	size_t		screen_width;
	size_t		screen_height;
};
typedef struct s_camera	t_camera;

struct s_camera_specs {
	t_point3	position;
	t_vec3		direction;
	double		fov_deg;
};
typedef struct s_camera_specs t_camera_specs;

t_camera	camera_new(t_camera_specs specs,
				size_t screen_width,
				size_t screen_height);

#endif // T_CAMERA_H
