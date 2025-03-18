#ifndef T_HITTABLE_H
#define T_HITTABLE_H

typedef struct s_sphere t_sphere;
typedef struct s_plane t_plane;
typedef struct s_cylinder t_cylinder;

enum e_hittable_type {
	HITTABLE_SPHERE,
	HITTABLE_PLANE,
	HITTABLE_CYLINDER,
};
typedef enum e_hittable_type	t_hittable_type;

typedef struct s_hittable t_hittable;
struct s_hittable {
	t_hittable_type object;
	union {
		t_sphere sphere;
		t_plane plane;
		t_cylinder cylinder;
	};
};

#endif // T_HITTABLE_H
