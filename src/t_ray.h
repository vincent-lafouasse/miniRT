#ifndef RAY_H
#define RAY_H

#include "math/t_vec3/t_vec3.h"

typedef struct s_ray {
    t_point3 origin;
    t_vec3 direction;
} t_ray;

t_ray ray_new(t_point3 origin, t_vec3 direction);

#endif
