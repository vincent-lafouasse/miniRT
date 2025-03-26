#include "./t_point_light_array.h"

#include <stdlib.h>

void point_light_array_destroy(t_point_light_array **self)
{
	free(*self);
	*self = NULL;
}
