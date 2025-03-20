#include "./t_hittable.h"

#include "./t_sphere.h"

#include "ray/t_ray.h"
#include "math/t_interval/t_interval.h"

#include <stdbool.h>
#include <stdlib.h>

bool sphere_hit(t_sphere sphere, t_interval range, t_ray ray, t_hit_record *rec);

bool object_hit(const t_hittable *object, t_interval range, t_ray ray, t_hit_record *rec_out)
{
	bool has_hit;

	if (object->type == HITTABLE_SPHERE)
		has_hit = sphere_hit(object->sphere, range, ray, rec_out);
	else
		abort(); // other shapes are unimplemented
	if (has_hit)
		rec_out->object = object;
	return has_hit;
}
