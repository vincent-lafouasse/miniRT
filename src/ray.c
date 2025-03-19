#include "ray.h"

t_ray ray_new(t_point3 origin, t_vec3 direction) {
    return (t_ray){origin, direction};
}
