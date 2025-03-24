#ifndef T_SPHERE_H
#define T_SPHERE_H

#include "math/t_vec3/t_vec3.h"
#include "math/t_rgb/t_rgb.h"

struct s_sphere {
	t_point3 origin;
	t_rgb color;
	double radius;
};
typedef struct s_sphere t_sphere;

t_sphere sphere_new(t_point3 origin, t_rgb color, double radius);
//t_hit_record sphere_hit(t_camera cam, t_ray ray);

#endif // T_SPHERE_H
