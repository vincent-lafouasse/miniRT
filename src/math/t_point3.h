#pragma once

#include <stdbool.h>

#include "t_tuple4.h"

typedef t_tuple4 t_point3;

t_point3 point_new(double x, double y, double z);
bool point_is_valid(t_point3 point);