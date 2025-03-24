#ifndef T_HITTABLE_H
#define T_HITTABLE_H

#include "./sphere/t_sphere.h"
#include "./plane/t_plane.h"
#include "./cylinder/t_cylinder.h"

#include "ray/t_ray.h"
#include "math/t_interval/t_interval.h"

enum e_hittable_type {
	HITTABLE_SPHERE,
	HITTABLE_PLANE,
	HITTABLE_CYLINDER,
};
typedef enum e_hittable_type	t_hittable_type;

typedef struct s_hittable t_hittable;
struct s_hittable {
	t_hittable_type type;
	union {
		t_sphere sphere;
		t_plane plane;
		t_cylinder cylinder;
	};
};

t_hittable	hittable_sphere_new(t_sphere sphere);
t_hittable	hittable_plane_new(t_plane plane);
t_hittable	hittable_cylinder_new(t_cylinder cylinder);

typedef struct s_hit_record t_hit_record;
struct s_hit_record {
	t_point3 point;
	double t;
	t_vec3 normal;
	const t_hittable *object;
};

bool object_hit(const t_hittable *object, t_interval range, t_ray ray, t_hit_record *rec_out);

#endif // T_HITTABLE_H
