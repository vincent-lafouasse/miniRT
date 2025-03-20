#ifndef T_HITTABLE_ARRAY_H
#define T_HITTABLE_ARRAY_H

#include "./t_hittable.h"
#include "math/t_interval/t_interval.h"
#include <stddef.h>
#include <stdbool.h>

struct s_hittable_array {
	size_t cap;
	size_t len;
	t_hittable data[];
};
typedef struct s_hittable_array t_hittable_array;

t_hittable_array *hittable_array_new(size_t cap);

typedef bool t_is_full;
t_is_full hittable_array_push(t_hittable_array *self, t_hittable hittable);

bool hittable_array_hit(const t_hittable_array *self, t_interval range, t_ray ray, t_hit_record *rec_out);

#endif // T_HITTABLE_ARRAY_H
