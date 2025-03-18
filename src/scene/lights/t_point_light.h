#ifndef T_POINT_LIGHT_H
#define T_POINT_LIGHT_H

#include "math/t_vec3/t_vec3.h"

struct s_point_light {
	t_vec3	coordinates;
	double	intensity;
	t_rgb	color;
};
typedef struct s_point_light t_point_light;

static inline t_point_light point_light(t_vec3 coordinates, double intensity, t_rgb color) {
	return ((t_point_light){.coordinates = coordinates, .intensity = intensity, .color = color});
}

#endif // T_POINT_LIGHT_H
