#pragma once

typedef struct
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_tuple4;

t_tuple4	tuple4_new(double x, double y, double z, double w);
t_tuple4	tuple4_add(t_tuple4 t1, t_tuple4 t2);
t_tuple4	tuple4_subtract(t_tuple4 t1, t_tuple4 t2);
t_tuple4	tuple4_negate(t_tuple4 t);
t_tuple4	tuple4_multiply(double s, t_tuple4 t);
int			tuple4_compare(t_tuple4 t1, t_tuple4 t2);