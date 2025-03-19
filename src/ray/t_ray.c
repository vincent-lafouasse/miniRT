#include "t_ray.h"

t_ray ray_new(t_point3 origin, t_vec3 direction) {
    return (t_ray){origin, direction};
}

t_point3 ray_at(t_ray ray, double t) {
    return vec3_add(ray.origin, vec3_mul(t, ray.direction));
}
