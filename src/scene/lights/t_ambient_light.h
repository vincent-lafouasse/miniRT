#ifndef T_AMBIENT_LIGHT_H
#define T_AMBIENT_LIGHT_H

#include "math/t_vec3/t_vec3.h"
#include "math/t_rgb/t_rgb.h"

struct s_ambient_light {
	double	intensity;
	t_rgb	color;
};
typedef struct s_ambient_light t_ambient_light;

static inline t_ambient_light ambient_light(double intensity, t_rgb color) {
	return ((t_ambient_light){.intensity = intensity, .color = color});
}

#endif // T_AMBIENT_LIGHT_H
