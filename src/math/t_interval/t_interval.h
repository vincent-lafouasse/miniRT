#ifndef T_INTERVAL_H
# define T_INTERVAL_H

#include <math.h>

struct s_interval {
	double min;
	double max;
};
typedef s_interval t_interval;

t_interval interval_new(double min, double max);
double interval_size(t_interval);
bool interval_contains(t_interval, double);
bool interval_surrounds(t_interval, double);

static t_interval empty_interval(void) {
	return (t_interval){.min = INFINITY, .max = -INFINITY};
}

static t_interval interval_R(void) {
	return (t_interval){.min = -INFINITY, .max = INFINITY};
}

static t_interval interval_R_plus(void) {
	return (t_interval){.min = 0.0, .max = INFINITY};
}

#endif // T_INTERVAL_H
