#include "math.h"

#include <math.h>

bool double_eq(const double a, const double b)
{
    return (fabs(a - b) < EPSILON);
}
