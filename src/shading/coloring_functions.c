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

// alternative entry point
t_rgb pixel_color_with_antialiasing(int x, int y, const t_camera* camera, const t_scene* scene) {
    t_point3 pixel_center = vec3_add(
        vec3_add(camera->pixel00, vec3_mul(x, camera->delta_u)),
        vec3_mul(y, camera->delta_v));

    t_point3 sub_pixel = vec3_add(pixel_center, vec3_div(vec3_add(camera->delta_u, camera->delta_v), 4.0));
    t_ray ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    t_rgb color = ray_color(ray, scene);

    sub_pixel = vec3_sub(sub_pixel, vec3_div(camera->delta_u, 2.0));
    ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    color = vec3_add(color, ray_color(ray, scene));

    sub_pixel = vec3_sub(sub_pixel, vec3_div(camera->delta_v, 2.0));
    ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    color = vec3_add(color, ray_color(ray, scene));

    sub_pixel = vec3_add(sub_pixel, vec3_div(camera->delta_u, 2.0));
    ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    color = vec3_add(color, ray_color(ray, scene));

    return vec3_div(color, 4.0);
}

t_rgb pixel_color_flat(int x, int y, const t_camera* camera, const t_scene* scene) {
    t_point3 pixel = vec3_add(
        vec3_add(camera->pixel00, vec3_mul(x, camera->delta_u)),
        vec3_mul(y, camera->delta_v));
    t_vec3 ray_direction = vec3_sub(pixel, camera->position);
    t_ray ray = ray_new(camera->position, ray_direction);

    t_hit_record _;
    bool hit = hittable_array_hit(scene->objects, interval_new(1024 * DOUBLE_EPSILON, INFINITY), ray, &_);

    if (!hit) {
        return vec3_new(0,0,0);
    } else {
        return vec3_new(1,1,1);
    }
}

// main entry point
t_rgb pixel_color(int x, int y, const t_camera* camera, const t_scene* scene) {
    t_point3 pixel = vec3_add(
        vec3_add(camera->pixel00, vec3_mul(x, camera->delta_u)),
        vec3_mul(y, camera->delta_v));
    t_vec3 ray_direction = vec3_sub(pixel, camera->position);
    t_ray ray = ray_new(camera->position, ray_direction);
    return ray_color(ray, scene);
}
