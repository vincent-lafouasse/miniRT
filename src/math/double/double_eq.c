#include "double.h"
#include <math.h>

bool double_eq(double a, double b) {
    double epsilon = 32 * DOUBLE_EPSILON;
    double abs_th = DOUBLE_MIN;

    if (a == b) return true;

    double diff = fabs(a-b);
    double norm = fmin((fabs(a) + fabs(b)), INFINITY);
    return diff < fmax(abs_th, epsilon * norm);
}
