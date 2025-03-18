#ifndef T_HITTABLE_H
#define T_HITTABLE_H

#include "./t_sphere.h"
#include "./t_plane.h"
#include "./t_cylinder.h"

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

#endif // T_HITTABLE_H
