#ifndef T_PLANE_H
#define T_PLANE_H

#include "math/t_vec3/t_vec3.h"

struct s_plane {
	t_point3 origin;
	t_vec3 normal;
	t_rgb color;
};
typedef struct s_plane t_plane;

t_plane plane_new(t_point3 origin, t_vec3 normal, t_rgb color);
//t_hit_record plane_hit(t_camera cam, t_ray ray);

#endif // T_PLANE_H
