#include "./t_hittable_array.h"

#include <stdlib.h>

t_hittable_array *hittable_array_new(size_t cap)
{
	t_hittable_array *alloc;

	alloc = malloc(sizeof(t_hittable_array) + sizeof(t_hittable) * cap);
	if (!alloc)
		return (NULL);
	*alloc = (t_hittable_array){.cap = cap, .len = 0};
	return (alloc);
}
