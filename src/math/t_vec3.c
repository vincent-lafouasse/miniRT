#include "t_vec3.h"

t_vec3 vec3_new(double x, double y, double z) {
    return tuple4_new(x, y, z, 0.0);
}

t_vec3 vec3_add(const t_vec3* v1, const t_vec3* v2) {
    return tuple4_add(v1, v2);
}

t_vec3 vec3_subtract(const t_vec3* v1, const t_vec3* v2) {
    return tuple4_add(v1, &(t_vec3){-v2->x, -v2->y, -v2->z, -v2->w});
}

t_vec3 vec3_multiply(double x, const t_vec3* v) {
    return (t_vec3){x * v->x, x * v->y, x * v->z, x * v->w};
}

t_vec3 vec3_negate(const t_vec3* v) {
    return tuple4_new(-v->x, -v->y, -v->z, -v->w);
}

double vec3_magnitude(const t_vec3* v);
t_vec3 vec3_normalize(const t_vec3* v);

double vec3_dot(const t_vec3* v1, const t_vec3* v2);
t_vec3 vec3_cross(const t_vec3* v1, const t_vec3* v2);

bool vec3_is_valid(t_vec3 vec) {
    return (vec.w == 0.0);
}
