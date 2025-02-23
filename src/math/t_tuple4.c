#include "t_tuple4.h"

t_tuple4 tuple4_new(double x, double y, double z, double w) {
    return (t_tuple4){x, y, z, w};
}

t_tuple4 tuple4_add(const t_tuple4* t1, const t_tuple4* t2) {
    return (t_tuple4){t1->x + t2->x, t1->y + t2->y, t1->z + t2->z,
                      t1->w + t2->w};
}

t_tuple4 tuple4_subtract(const t_tuple4* t1, const t_tuple4* t2) {
    return (t_tuple4){t1->x - t2->x, t1->y - t2->y, t1->z - t2->z,
                      t1->w - t2->w};
}

t_tuple4 tuple4_negate(const t_tuple4* t) {
    return (t_tuple4){-t->x, -t->y, -t->z, -t->w};
}

t_tuple4 tuple4_multiply(double s, const t_tuple4* t) {
    return (t_tuple4){s * t->x, s * t->y, s * t->z, s * t->w};
}

int tuple4_compare(const t_tuple4* t1, const t_tuple4* t2) {
    if (t1->x != t2->x)
        return t1->x - t2->x;
    if (t1->y != t2->y)
        return t1->y - t2->y;
    if (t1->z != t2->z)
        return t1->z - t2->z;
    if (t1->w != t2->w)
        return t1->w - t2->w;
    return 0;
}
