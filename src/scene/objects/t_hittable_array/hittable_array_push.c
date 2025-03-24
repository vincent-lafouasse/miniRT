#include "t_hittable_array.h"

t_is_full hittable_array_push(t_hittable_array *self, const t_hittable hittable)
{
	if (self->cap == self->len)
		return (true);
	self->data[self->len++] = hittable;
	return (false);
}
