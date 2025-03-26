#include "./t_point_light_array.h"

#include <stdlib.h>

t_point_light_array *point_light_array_new(size_t cap)
{
	t_point_light_array *alloc;

	alloc = malloc(sizeof(t_point_light_array) + sizeof(t_point_light) * cap);
	if (!alloc)
		return (NULL);
	*alloc = (t_point_light_array){.cap = cap, .len = 0};
	return (alloc);
}
