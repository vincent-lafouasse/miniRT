#ifndef SHADING_H
#define SHADING_H

#include "math/t_rgb/t_rgb.h"
#include "camera/t_camera.h"
#include "scene/t_scene.h"

t_rgb pixel_color(int x, int y, const t_camera* camera, const t_scene* scene);
t_rgb pixel_color_with_antialiasing(int x, int y, const t_camera* camera, const t_scene* scene);
t_rgb pixel_color_flat(int x, int y, const t_camera* camera, const t_scene* scene);

#endif
