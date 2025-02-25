#include "t_tuple4.h"

t_tuple4	tuple4_new(double x, double y, double z, double w)
{
	return ((t_tuple4){x, y, z, w});
}

t_tuple4	tuple4_add(t_tuple4 t1, t_tuple4 t2)
{
	return (tuple4_new(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w));
}

t_tuple4	tuple4_subtract(t_tuple4 t1, t_tuple4 t2)
{
	return (tuple4_add(t1, tuple4_negate(t2)));
}

t_tuple4	tuple4_negate(t_tuple4 t)
{
	return (tuple4_new(-t.x, -t.y, -t.z, -t.w));
}

t_tuple4	tuple4_multiply(double s, t_tuple4 t)
{
	return (tuple4_new(s * t.x, s * t.y, s * t.z, s * t.w));
}

// this is terrible
int	tuple4_compare(t_tuple4 t1, t_tuple4 t2)
{
	if (t1.x != t2.x)
		return (t1.x - t2.x);
	if (t1.y != t2.y)
		return (t1.y - t2.y);
	if (t1.z != t2.z)
		return (t1.z - t2.z);
	if (t1.w != t2.w)
		return (t1.w - t2.w);
	return (0);
}
