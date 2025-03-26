#include "shading.h"

#include "math/double/double.h"
#include "./t_material.h"

t_rgb sum_shadings(t_material material, t_rgb ambient, t_rgb diffuse, t_rgb specular) {
    t_rgb out = vec3_mul(material.ambient, ambient);
    out = vec3_add(vec3_mul(material.diffuse, diffuse), out);
    out = vec3_add(vec3_mul(material.specular, specular), out);
    return out;
}

t_rgb hit_color(t_hit_record hit, t_ray r, const t_scene* scene) {
    t_material material = material_default(); // object property ?

    t_rgb ambient = ambient_shading(scene->ambient_light);

    t_rgb diffuse = total_diffuse_shading(hit, scene->point_lights, scene->objects);
    t_rgb specular = total_specular_shading(hit, scene->point_lights, r, material.alpha, scene->objects);

    return sum_shadings(material, ambient, diffuse, specular);
}

t_rgb ray_color(t_ray r, const t_scene* scene) {
    t_hit_record rec;
    bool hit = hittable_array_hit(scene->objects, interval_new(1024 * DOUBLE_EPSILON, INFINITY), r, &rec);

    if (hit) {
        return hit_color(rec, r, scene);
    } else {
        return rgb_black();
    }
}
