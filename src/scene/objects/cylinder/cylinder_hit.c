#include "../t_hittable.h"

#include "math/t_interval/t_interval.h"
#include "ray/t_ray.h"

#include <stdbool.h>

bool cylinder_endcap_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);
bool cylinder_shaft_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec);

bool cylinder_hit(t_cylinder cylinder, t_interval range, t_ray ray, t_hit_record *rec)
{
	bool shaft_hit;
	bool cap_hit;
	t_hit_record shaft_hit_rec;
	t_hit_record cap_hit_rec;

	shaft_hit = cylinder_shaft_hit(cylinder, range, ray, &shaft_hit_rec);
	cap_hit = cylinder_endcap_hit(cylinder, range, ray, &cap_hit_rec);

	if (shaft_hit && cap_hit) {
		if (shaft_hit_rec.t < cap_hit_rec.t)
		{
			*rec = shaft_hit_rec;
			return true;
		}
		else
		{
			*rec = cap_hit_rec;
			return true;
		}
	}
	else if (shaft_hit)
	{
		*rec = shaft_hit_rec;
		return true;
	}
	else if (cap_hit)
	{
		*rec = cap_hit_rec;
		return true;
	}
	return false;
}
