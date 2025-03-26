#include "./t_camera.h"

#include "scene/t_scene.h"
#include "ray/t_ray.h"

#include "math/double/double.h"
#include "math/t_rgb/t_rgb.h"
#include "math/t_vec3/t_vec3.h"

// alternative entry point
t_rgb camera_pixel_color_with_antialiasing(const t_camera* camera, const t_scene* scene, int x, int y) {
    t_point3 pixel_center = vec3_add(
        vec3_add(camera->pixel00, vec3_mul(x, camera->delta_u)),
        vec3_mul(y, camera->delta_v));

    t_point3 sub_pixel = vec3_add(pixel_center, vec3_div(vec3_add(camera->delta_u, camera->delta_v), 4.0));
    t_ray ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    t_rgb color = scene_ray_color(scene, ray);

    sub_pixel = vec3_sub(sub_pixel, vec3_div(camera->delta_u, 2.0));
    ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    color = vec3_add(color, scene_ray_color(scene, ray));

    sub_pixel = vec3_sub(sub_pixel, vec3_div(camera->delta_v, 2.0));
    ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    color = vec3_add(color, scene_ray_color(scene, ray));

    sub_pixel = vec3_add(sub_pixel, vec3_div(camera->delta_u, 2.0));
    ray = ray_new(camera->position, vec3_sub(sub_pixel, camera->position));
    color = vec3_add(color, scene_ray_color(scene, ray));

    return vec3_div(color, 4.0);
}

t_rgb camera_pixel_color_flat(const t_camera* camera, const t_scene* scene, int x, int y) {
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
t_rgb camera_pixel_color(const t_camera* camera, const t_scene* scene, int x, int y) {
    t_point3 pixel = vec3_add(
        vec3_add(camera->pixel00, vec3_mul(x, camera->delta_u)),
        vec3_mul(y, camera->delta_v));
    t_vec3 ray_direction = vec3_sub(pixel, camera->position);
    t_ray ray = ray_new(camera->position, ray_direction);
    return scene_ray_color(scene, ray);
}
