#ifndef T_ELEMENT_H
# define T_ELEMENT_H

# include "math/t_vec3/t_vec3.h"

# include <stdint.h>

# define TAG_AMBIENT_LIGHT "A"
# define TAG_CAMERA "C"
# define TAG_LIGHT "L"
# define TAG_SPHERE "sp"
# define TAG_PLANE "pl"
# define TAG_CYLINDER "cy"

typedef enum e_element_kind t_element_kind;
enum e_element_kind {
	ELEM_AMBIENT_LIGHT,
	ELEM_CAMERA,
	ELEM_LIGHT,
	ELEM_SPHERE_PRIMITIVE,
	ELEM_PLANE_PRIMITIVE,
	ELEM_CYLINDER_PRIMITIVE,
};

typedef struct s_ambient_light_element t_ambient_light_element;
struct s_ambient_light_element {
	// 0.0 <= lighting_ratio <= 1.0
	double	lighting_ratio;
	// 0 <= color[n] <= 255
	uint8_t	color[3];
};

typedef struct s_camera_element t_camera_element;
struct s_camera_element {
	t_vec3	coordinates;
	// is normalized; each axis ∈ [-1.0; 1.0]
	t_vec3	orientation;
	// 0 <= fov <= 180
	uint8_t	fov;
};

typedef struct s_light_element t_light_element;
struct s_light_element {
	t_vec3	coordinates;
	// 0.0 <= brightness_ratio <= 1.0
	double	brightness_ratio;
	// 0 <= color[n] <= 255
	uint8_t	color[3]; // unused in mandatory
};

typedef struct s_sphere_element t_sphere_element;
struct s_sphere_element {
	t_vec3	center;
	double	diameter;
	// 0 <= color[n] <= 255
	uint8_t	color[3];
};

typedef struct s_plane_element t_plane_element;
struct s_plane_element {
	t_point3	point;
	// is normalized; each axis ∈ [-1.0; 1.0]
	t_vec3		normal;
	// 0 <= color[n] <= 255
	uint8_t		color[3];
};

typedef struct s_cylinder_element t_cylinder_element;
struct s_cylinder_element {
	t_point3	point;
	// is normalized; each axis ∈ [-1.0; 1.0]
	t_vec3		axis;
	double		diameter;
	double		height;
	// 0 <= color[n] <= 255
	uint8_t		color[3];
};

typedef struct s_element t_element;
struct s_element {
	t_element_kind	kind;
	union
	{
		t_ambient_light_element	ambient;
		t_camera_element		camera;
		t_light_element			light;
		t_sphere_element		sphere;
		t_plane_element			plane;
		t_cylinder_element		cylinder;
	};
};

#endif // T_ELEMENT_H
