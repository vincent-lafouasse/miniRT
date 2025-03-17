#ifndef T_INTERVAL_H
# define T_INTERVAL_H

struct s_interval {
	double min;
	double max;
};
typedef s_interval t_interval;

t_interval interval_new(double min, double max);

#endif // T_INTERVAL_H
