#ifndef T_PLANE_H
#define T_PLANE_H

#include "error/t_error.h"

#include "math/t_vec3/t_vec3.h"
#include "math/t_rgb/t_rgb.h"

struct s_plane {
	t_point3 origin;
	t_vec3 normal;
	t_rgb color;
};
typedef struct s_plane t_plane;

t_error plane_new(t_point3 origin, t_vec3 normal, t_rgb color, t_plane *out);
//t_hit_record plane_hit(t_camera cam, t_ray ray);

#endif // T_PLANE_H
