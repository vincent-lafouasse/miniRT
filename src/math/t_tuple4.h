#pragma once

typedef struct {
    double x;
    double y;
    double z;
    double w;
} t_tuple4;

t_tuple4 tuple4_new(double x, double y, double z, double w);
t_tuple4 tuple4_add(const t_tuple4* t1, const t_tuple4* t2);
t_tuple4 tuple4_subtract(const t_tuple4* t1, const t_tuple4* t2);
t_tuple4 tuple4_negate(const t_tuple4* t);
t_tuple4 tuple4_multiply(double s, const t_tuple4* t);
int tuple4_compare(const t_tuple4* t1, const t_tuple4* t2);