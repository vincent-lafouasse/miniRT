#pragma once

#include <stdbool.h>

#include "t_tuple4.h"

typedef t_tuple4 t_vec3;

t_vec3 vec_new(double x, double y, double z);
bool vec_is_valid(t_vec3 vec);