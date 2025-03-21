#include "math/t_vec3/t_vec3.h"
#include "ray/t_ray.h"
#include "parser/parse.h"
#include "render/t_renderer.h"
#include "scene/objects/t_hittable.h"
#include "math/t_interval/t_interval.h"
#include "scene/objects/t_hittable_array.h"
#include "scene/t_scene.h"

#include <assert.h>

#define BALLS                              \
    "C  0,0,0       0,0,-1  120      \n"    \
    "A  0.15        255,255,255     \n"    \
    "L  5,4,0       0.42    255,255,255\n" \
    "sp 0,0,-1      1.0       2,62,138\n"  \
    "sp 0,-100.5,-1      200       20,200,100\n"

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
        .ambient = 0.2,
        .diffuse = 1.0,
        .specular = 1.0,
        .alpha = 10,
    };
}

#define DBL_EPSILON 0.0000001

t_rgb ray_color(t_ray r, const t_scene* scene) {
    t_hit_record rec;
    bool hit = hittable_array_hit(scene->objects, interval_R_plus(), r, &rec);

    if (!hit) {
        return vec3_new(0,0,0);
    }

    t_rgb object_color = rec.object->sphere.color;
    t_material material = material_default();

    t_vec3 hit_to_light = vec3_sub(scene->point_light.coordinates, rec.point);
    double distance_to_light = vec3_length(hit_to_light);
    t_vec3 hit_to_light_unit = vec3_normalize(hit_to_light);

    t_rgb ambient = vec3_mul(scene->ambient_light.intensity, scene->ambient_light.color);

    t_hit_record _;
    if (hittable_array_hit(scene->objects, interval_new(DBL_EPSILON, distance_to_light), (t_ray){.origin = rec.point, .direction = hit_to_light_unit} , &_))
        return vec3_mul(material.ambient, ambient);

    double diffuse_weight = scene->point_light.intensity * vec3_dot(rec.normal, hit_to_light_unit);
    diffuse_weight = fmax(0.0, diffuse_weight);
    t_rgb diffuse = vec3_mul(diffuse_weight, object_color); // should mix color with point_light color

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
    t_rgb specular = vec3_mul(specular_weight, vec3_new(1,1,1));

    t_rgb out = vec3_new(0, 0, 0);
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

static t_error renderer_init_with_exit_hooks(size_t width, double aspect_ratio, t_renderer *out);

int main(void) {
    t_renderer renderer;
    t_error err = renderer_init_with_exit_hooks(WIDTH, ASPECT_RATIO, &renderer);
    if (err != NO_ERROR)
        return (EXIT_FAILURE);

    t_camera_specs specs;
    t_scene scene;
    parse(BALLS, &specs, &scene);
    t_camera camera = camera_new(specs, renderer.width, renderer.height);

    render(&camera, &scene, &renderer, pixel_color);
    scene_destroy(&scene);
    renderer_destroy(&renderer);
}

static t_error renderer_init_with_exit_hooks(size_t width, double aspect_ratio, t_renderer *out)
{
    t_error err = renderer_init(width, aspect_ratio, out);
    if (err == NO_ERROR) {
        renderer_set_exit_loop_on_esc(out);
        renderer_set_exit_loop_on_cross(out);
    }

    return (err);
}
