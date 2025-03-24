#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"
#include "parser/parse.h"
#include "render/t_renderer.h"
#include "scene/objects/t_hittable.h"
#include "math/t_interval/t_interval.h"
#include "scene/objects/t_hittable_array/t_hittable_array.h"
#include "scene/t_scene.h"

#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point2;

struct s_material {
    double ambient;
    double diffuse;
    double specular;
    double alpha;
};
typedef struct s_material t_material;

t_material material_default(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 0.5,
        .alpha = 10,
    };
}

t_material material_matte(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 0.3,
        .alpha = 5,
    };
}

t_material material_shiny(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 0.8,
        .alpha = 50,
    };
}

#define DBL_EPSILON 0.0000001

t_rgb ray_color(t_ray r, const t_scene* scene) {
    t_hit_record rec;
    bool hit = hittable_array_hit(scene->objects, interval_new(DBL_EPSILON, INFINITY), r, &rec);

    if (!hit) {
        return vec3_new(0,0,0);
    }

    t_rgb obj_color = object_color(rec.object);
    t_material material = material_shiny();

    t_vec3 hit_to_light = vec3_sub(scene->point_light.coordinates, rec.point);
    double distance_to_light = vec3_length(hit_to_light);
    t_vec3 hit_to_light_unit = vec3_normalize(hit_to_light);

    t_rgb ambient = vec3_mul(scene->ambient_light.intensity, scene->ambient_light.color);

    t_hit_record _;
    if (hittable_array_hit(scene->objects, interval_new(DBL_EPSILON, distance_to_light), (t_ray){.origin = rec.point, .direction = hit_to_light_unit} , &_))
        return vec3_mul(material.ambient, ambient);

    double diffuse_weight = scene->point_light.intensity * vec3_dot(rec.normal, hit_to_light_unit);
    diffuse_weight = fmax(0.0, diffuse_weight);
    t_rgb diffuse = vec3_mul(diffuse_weight, obj_color); // this supposes the point light is white
                                                            // bonuses require that we mix the colors

    double specular_intensity = 1.0; // should come from .rt, should probably be a point light property
    t_vec3 perfect_specular_direction = vec3_mul(2.0 * vec3_dot(hit_to_light_unit, rec.normal), rec.normal);
    perfect_specular_direction = vec3_sub(perfect_specular_direction, hit_to_light_unit);
    perfect_specular_direction = vec3_normalize(perfect_specular_direction);
    double specular_weight = specular_intensity * pow(
        vec3_dot(
            perfect_specular_direction, vec3_normalize(r.direction)
        ),
        material.alpha
    );
    specular_weight = fmax(0.0, specular_weight);
    if (diffuse_weight == 0.0) // safe check as it is explicitely set to 0.0
        specular_weight = 0.0;
    t_rgb specular = vec3_mul(specular_weight, rgb_white());

    t_rgb out = rgb_black();
    out = vec3_add(
        out,
        vec3_mul(material.ambient, ambient));
    out = vec3_add(
        out,
        vec3_mul(material.diffuse, diffuse));
    out = vec3_add(
        out,
        vec3_mul(material.specular, specular));

    return out;
}

typedef t_rgb (*t_coloring_ft)(Point2, const t_camera*, const t_scene*);

// alternative entry point
t_rgb pixel_color_with_antialiasing(Point2 px, const t_camera* camera, const t_scene* scene) {
    t_point3 pixel_center = vec3_add(
        vec3_add(camera->pixel00, vec3_mul((double)px.x, camera->delta_u)),
        vec3_mul((double)px.y, camera->delta_v));

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

t_rgb pixel_color_flat(Point2 px, const t_camera* camera, const t_scene* scene) {
    t_point3 pixel = vec3_add(
        vec3_add(camera->pixel00, vec3_mul((double)px.x, camera->delta_u)),
        vec3_mul((double)px.y, camera->delta_v));
    t_vec3 ray_direction = vec3_sub(pixel, camera->position);
    t_ray ray = ray_new(camera->position, ray_direction);

    t_hit_record _;
    bool hit = hittable_array_hit(scene->objects, interval_new(DBL_EPSILON, INFINITY), ray, &_);

    if (!hit) {
        return vec3_new(0,0,0);
    } else {
        return vec3_new(1,1,1);
    }
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
    renderer_flush_pixels(renderer);

    renderer_enter_loop(renderer);
}

#define WIDTH 2000
#define ASPECT_RATIO (16.0 / 9.0)

#include <stdlib.h>

int main(int argc, char **argv) {
    t_renderer renderer;
    t_error err = renderer_init_with_exit_hooks(WIDTH, ASPECT_RATIO, &renderer);
    if (err != NO_ERROR)
    {
        printf("Error: %s\n", error_repr(err));
        return (EXIT_FAILURE);
    }

    t_camera_specs specs;
    t_scene scene;
    if (argc != 2)
    {
        printf("Error: %s\n", error_repr(E_BAD_PROGRAM_USAGE));
        return (EXIT_FAILURE);
    }
    err = parse_from_file(argv[1], &specs, &scene);
    if (err != NO_ERROR)
    {
        printf("Error: %s\n", error_repr(err));
        return (EXIT_FAILURE);
    }
    t_camera camera = camera_new(specs, renderer.width, renderer.height);

    render(&camera, &scene, &renderer, pixel_color);
    scene_destroy(&scene);
    renderer_destroy(&renderer);
}
