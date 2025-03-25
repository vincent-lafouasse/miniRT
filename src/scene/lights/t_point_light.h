#ifndef T_POINT_LIGHT_H
#define T_POINT_LIGHT_H

#include "error/t_error.h"
#include "math/t_vec3/t_vec3.h"
#include "math/t_rgb/t_rgb.h"

struct s_point_light {
	t_vec3	coordinates;
	double	intensity;
	t_rgb	color;
};
typedef struct s_point_light t_point_light;

static inline t_error point_light(t_point3 coordinates, double intensity, t_rgb color, t_point_light *out) {
	if (intensity < 0.0 || intensity > 1.0)
		return (E_OUT_OF_RANGE);
	*out = ((t_point_light){.coordinates = coordinates, .intensity = intensity, .color = color});
	return (NO_ERROR);
}

#endif // T_POINT_LIGHT_H
