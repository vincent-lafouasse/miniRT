#include "math.h"
#include <math.h>

bool	double_eq(const double a, const double b)
{
	return (fabs(a - b) < EPSILON);
}

int	double_cmp(double a, double b)
{
	if (double_eq(a, b))
		return (0);
	return (2.0 * (a - b) / fabs(a - b));
}
