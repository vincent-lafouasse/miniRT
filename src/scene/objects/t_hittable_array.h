#ifndef T_HITTABLE_ARRAY_H
#define T_HITTABLE_ARRAY_H

#include "./t_hittable.h"
#include <stddef.h>

struct s_hittable_array {
	size_t cap;
	size_t len;
	t_hittable data[];
};
typedef struct s_hittable_array t_hittable_array;

t_hittable_array *hittable_array_new(size_t cap);

#endif // T_HITTABLE_ARRAY_H
