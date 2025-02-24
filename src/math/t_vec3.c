#include "t_vec3.h"

t_vec3 vec3_new(double x, double y, double z) {
    return tuple4_new(x, y, z, 0.0);
}

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2) {
    return tuple4_add(v1, v2);
}

t_vec3 vec3_subtract(t_vec3 v1, t_vec3 v2) {
    return tuple4_add(v1, vec3_negate(v2));
}

t_vec3 vec3_multiply(double x, t_vec3 v) {
    return tuple4_new(x * v.x, x * v.y, x * v.z, x * v.w);
}

t_vec3 vec3_negate(t_vec3 v) {
    return tuple4_new(-v.x, -v.y, -v.z, -v.w);
}

double vec3_magnitude(t_vec3 v);
t_vec3 vec3_normalize(t_vec3 v);

double vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2);

bool vec3_is_valid(t_vec3 vec) {
    return (vec.w == 0.0);
}
