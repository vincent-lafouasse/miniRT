#ifndef SHADING_H
#define SHADING_H

#include "math/t_rgb/t_rgb.h"
#include "camera/t_camera.h"
#include "scene/t_scene.h"

t_rgb pixel_color(int x, int y, const t_camera* camera, const t_scene* scene);
t_rgb pixel_color_with_antialiasing(int x, int y, const t_camera* camera, const t_scene* scene);
t_rgb pixel_color_flat(int x, int y, const t_camera* camera, const t_scene* scene);

t_rgb ambient_shading(t_ambient_light light);
t_rgb total_diffuse_shading(t_hit_record hit, const t_point_light_array *lights, const t_hittable_array* objects);
t_rgb total_specular_shading(t_hit_record hit, t_point_light_array *lights, t_ray r, double alpha, const t_hittable_array* objects);

bool hit_is_in_shadow(t_hit_record rec, const t_hittable_array* objects, t_point_light light);

#endif
