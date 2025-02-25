#pragma once

#include "t_tuple4.h"
#include <stdbool.h>

typedef t_tuple4	t_vec3;

t_vec3				vec3_new(double x, double y, double z);
t_vec3				vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_subtract(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_multiply(double x, t_vec3 v);
t_vec3				vec3_negate(t_vec3 v);

double				vec3_magnitude(t_vec3 v);
t_vec3				vec3_normalize(t_vec3 v);

double				vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_cross(t_vec3 v1, t_vec3 v2);

bool				vec3_is_valid(t_vec3 vec);