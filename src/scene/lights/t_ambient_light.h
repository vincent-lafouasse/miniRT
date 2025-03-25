#ifndef T_AMBIENT_LIGHT_H
#define T_AMBIENT_LIGHT_H

#include "error/t_error.h"

#include "math/t_vec3/t_vec3.h"
#include "math/t_rgb/t_rgb.h"

struct s_ambient_light {
	double	intensity;
	t_rgb	color;
};
typedef struct s_ambient_light t_ambient_light;

static inline t_error ambient_light(double intensity, t_rgb color, t_ambient_light *out) {
	if (intensity < 0.0 || intensity > 1.0)
		return (E_OUT_OF_RANGE);
	*out = ((t_ambient_light){.intensity = intensity, .color = color});
	return (NO_ERROR);
}

#endif // T_AMBIENT_LIGHT_H
