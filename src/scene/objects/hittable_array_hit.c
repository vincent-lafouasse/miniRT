#include "./t_hittable_array.h"

#include "ray/t_ray.h"
#include "math/t_interval/t_interval.h"
#include "scene/objects/t_hittable.h"

#include <stdbool.h>
#include <stddef.h>

bool hittable_array_hit(const t_hittable_array *self, t_interval range, t_ray ray, t_hit_record *rec_out)
{
	size_t i;
	t_hit_record current;
	bool hit_something;
	t_hit_record nearest;

	i = 0;
	hit_something = false;
	while (i < self->len) {
		if (object_hit(&self->data[i], range, ray, &current)) {
			range.max = current.t;
			hit_something = true;
			nearest = current;
		}
		i++;
	}
	if (hit_something)
		*rec_out = nearest;
	return (hit_something);
}
