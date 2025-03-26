#include "shading.h"

#include "math/double/double.h"

bool hit_is_in_shadow(t_hit_record rec, const t_hittable_array* objects, t_point_light light) {
    t_vec3 hit_to_light = vec3_sub(light.coordinates, rec.point);
    double distance_to_light = vec3_length(hit_to_light);
    t_vec3 hit_to_light_unit = vec3_div(hit_to_light, distance_to_light);

    t_hit_record _;
    return hittable_array_hit(objects, interval_new(1024 * distance_to_light * DOUBLE_EPSILON, distance_to_light), (t_ray){.origin = rec.point, .direction = hit_to_light_unit} , &_);
}
