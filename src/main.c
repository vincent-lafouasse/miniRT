#include "error/t_error.h"
#include "math/t_rgb/t_rgb.h"
#include "parser/parse.h"
#include "render/t_renderer.h"
#include "scene/t_scene.h"

#include <stdio.h>

#define WIDTH 1000
#define ASPECT_RATIO (16.0 / 9.0)

#include <stdlib.h>

t_error parse_map(const char *filename, t_camera *cam_out, t_scene *scene_out)
{
    t_error err;
    t_camera_specs specs;
    t_scene scene;
    t_camera camera;

    err = parse_from_file(filename, &specs, &scene);
    if (err != NO_ERROR)
        return (err);
    err = camera_new(specs, WIDTH, WIDTH / (double)ASPECT_RATIO, &camera);
    if (err != NO_ERROR)
    {
        scene_destroy(&scene);
        return (err);
    }
    *cam_out = camera;
    *scene_out = scene;
    return (NO_ERROR);
}

int main(int argc, char **argv) {
    t_error err;
    t_camera camera;
    t_scene scene;
    t_renderer renderer;

    if (argc != 2)
        die(E_BAD_PROGRAM_USAGE, EXIT_FAILURE);
    err  = parse_map(argv[1], &camera, &scene);
    if (err != NO_ERROR)
        die(err, EXIT_FAILURE);
    err = renderer_init_with_exit_hooks(WIDTH, ASPECT_RATIO, &renderer);
    if (err != NO_ERROR)
    {
        scene_destroy(&scene);
        die(err, EXIT_FAILURE);
    }
    camera_render_scene(&camera, &scene, &renderer);
    scene_destroy(&scene);
    renderer_destroy(&renderer);
}
