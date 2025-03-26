#include "shading.h"

#include "math/double/double.h"

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
        .specular = 1.0,
        .alpha = 40,
    };
}

t_material material_matte(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 0.3,
        .alpha = 20,
    };
}

t_material material_shiny(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 5.0,
        .alpha = 200,
    };
}

bool hit_is_in_shadow(t_hit_record rec, const t_hittable_array* objects, t_point_light light) {
    t_vec3 hit_to_light = vec3_sub(light.coordinates, rec.point);
    double distance_to_light = vec3_length(hit_to_light);
    t_vec3 hit_to_light_unit = vec3_div(hit_to_light, distance_to_light);

    t_hit_record _;
    return hittable_array_hit(objects, interval_new(1024 * distance_to_light * DOUBLE_EPSILON, distance_to_light), (t_ray){.origin = rec.point, .direction = hit_to_light_unit} , &_);
}

t_rgb ambient_shading(t_ambient_light light) {
    return vec3_mul(light.intensity, light.color);
}

t_rgb diffuse_shading(t_hit_record hit, t_point_light light) {
    t_vec3 hit_to_light;
    double diffuse_weight;

    hit_to_light = vec3_sub(light.coordinates, hit.point);
    hit_to_light = vec3_normalize(hit_to_light);
    diffuse_weight = light.intensity * vec3_dot(hit.normal, hit_to_light);
    diffuse_weight = fmax(0.0, diffuse_weight);
    // this supposes the point light is white
    // bonuses require that we mix the colors
    return vec3_mul(diffuse_weight, object_color(hit.object));
}

t_rgb total_diffuse_shading(t_hit_record hit, const t_point_light_array *lights, const t_hittable_array* objects) {
    size_t i;
    t_rgb col;
    t_point_light current_light;

    i = 0;
    col = rgb_black();
    while (i < lights->len)
    {
        current_light = lights->data[i];
        if (!hit_is_in_shadow(hit, objects, current_light)) {
            col = vec3_add(col, diffuse_shading(hit, current_light));
        }
        i++;
    }
    return col;
}

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
