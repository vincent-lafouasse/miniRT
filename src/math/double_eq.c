#include <float.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

bool double_eq(double a, double b) {
    double epsilon = 32 * DBL_EPSILON;
    double abs_th = DBL_MIN;

    if (a == b) return true;

    double diff = fabs(a-b);
    double norm = fmin((fabs(a) + fabs(b)), INFINITY);
    return diff < fmax(abs_th, epsilon * norm);
}