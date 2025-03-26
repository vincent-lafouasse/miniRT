#include "t_point_light_array.h"

t_is_full point_light_array_push(t_point_light_array *self, const t_point_light point_light)
{
	if (self->cap == self->len)
		return (true);
	self->data[self->len++] = point_light;
	return (false);
}
