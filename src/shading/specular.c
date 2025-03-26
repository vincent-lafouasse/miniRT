#include "shading.h"

t_rgb specular_shading(t_hit_record hit, t_point_light light, t_ray r, double alpha) {
    t_vec3 hit_to_light;
    hit_to_light = vec3_sub(light.coordinates, hit.point);
    hit_to_light = vec3_normalize(hit_to_light);

    t_vec3 bissectrice = vec3_sub(hit_to_light, r.direction);
    bissectrice = vec3_normalize(bissectrice);
    double specular_weight = light.intensity * pow(
        vec3_dot(
            hit.normal, bissectrice
        ),
        alpha
    );
    specular_weight = fmax(0.0, specular_weight);
    return vec3_mul(specular_weight, rgb_white());
}

t_rgb total_specular_shading(t_hit_record hit, t_point_light_array *lights, t_ray r, double alpha, const t_hittable_array* objects) {
    size_t i;
    t_rgb col;
    t_point_light current_light;

    i = 0;
    col = rgb_black();
    while (i < lights->len)
    {
        current_light = lights->data[i];
        if (!hit_is_in_shadow(hit, objects, current_light)) {
            col = vec3_add(col, specular_shading(hit, current_light, r, alpha));
        }
        i++;
    }
    return col;
}
