#include "ray/t_ray.h"
#include "parser/parse.h"
#include "render/hooks.h"
#include "render/t_renderer.h"
#include "scene/objects/t_hittable.h"
#include "math/t_interval/t_interval.h"
#include "scene/objects/t_hittable_array.h"

#define BALLS                              \
    "C  0,0,0       0,0,-1  90      \n"    \
    "A  0.50        255,255,255     \n"    \
    "L  5,4,0       0.42    255,255,255\n" \
    "sp 0,0,-1      0.5       2,62,138\n"  \
    "sp 0,-100.5,-1      200       20,200,100\n"

typedef struct {
    int x;
    int y;
} Point2;

typedef t_rgb (*t_coloring_ft)(Point2, const t_camera*, const t_scene*);


t_rgb ray_color(t_ray r, const t_scene* scene) {
    t_hit_record rec;
    bool hit = hittable_array_hit(scene->objects, interval_R_plus(), r, &rec);

    if (!hit) {
        return vec3_new(0,0,0);
    }

    t_rgb color = vec3_div(vec3_add(rec.normal, vec3_new(1, 1, 1)), 2);

    return color;
}

// main entry point
t_rgb pixel_color(Point2 px, const t_camera* camera, const t_scene* scene) {
    t_point3 pixel = vec3_add(
        vec3_add(camera->pixel00, vec3_mul((double)px.x, camera->delta_u)),
        vec3_mul((double)px.y, camera->delta_v));
    t_vec3 ray_direction = vec3_sub(pixel, camera->position);
    t_ray ray = ray_new(camera->position, ray_direction);
    return ray_color(ray, scene);
}

#include "mlx.h"
#include <X11/X.h>

// will be hidden
void render(const t_camera* camera,
            const t_scene* scene,
            t_renderer* renderer,
            t_coloring_ft coloring_ft) {
    for (size_t x = 0; x < renderer->width; x++) {
        for (size_t y = 0; y < renderer->height; y++) {
            Point2 pixel = (Point2){.x = (int)x, .y = (int)y};
            t_rgb color = (*coloring_ft)(pixel, camera, scene);
            renderer_put_pixel(renderer, x, y, rgb_to_bytes(color));
        }
    }
    mlx_put_image_to_window(renderer->mlx, renderer->window, renderer->img, 0,
                            0);

    mlx_hook(renderer->window, DestroyNotify, StructureNotifyMask, exit_hook,
             renderer->mlx);
    mlx_key_hook(renderer->window, key_hook, renderer->mlx);
    mlx_loop(renderer->mlx);
}

#define WIDTH 700
#define ASPECT_RATIO (16.0 / 9.0)

int main(void) {
    t_renderer renderer = renderer_init(WIDTH, ASPECT_RATIO);

    t_camera_specs specs;
    t_scene scene;
    parse(BALLS, &specs, &scene);
    t_camera camera = camera_new(specs, renderer.width, renderer.height);

    render(&camera, &scene, &renderer, pixel_color);
}
