#include "shading.h"

t_rgb ambient_shading(t_ambient_light light) {
    return vec3_mul(light.intensity, light.color);
}
