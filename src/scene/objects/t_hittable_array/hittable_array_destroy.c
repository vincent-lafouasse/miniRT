#include "./t_hittable_array.h"

#include <stdlib.h>

void hittable_array_destroy(t_hittable_array **self)
{
	free(*self);
	*self = NULL;
}
