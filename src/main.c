#include "math/t_rgb/t_rgb.h"
#include "parser/parse.h"
#include "render/t_renderer.h"
#include "scene/t_scene.h"

#include <stdio.h>

// will be hidden
void render(const t_camera* camera,
            const t_scene* scene,
            t_renderer* renderer) {
    for (size_t x = 0; x < renderer->width; x++) {
        printf("%zu/%zu\n", x, renderer->width);
        for (size_t y = 0; y < renderer->height; y++) {
            t_rgb color = camera_pixel_color(camera, scene, x, y);
            renderer_put_pixel(renderer, x, y, rgb_to_bytes(color));
        }
    }
    renderer_flush_pixels(renderer);

    renderer_enter_loop(renderer);
}

#define WIDTH 1000
#define ASPECT_RATIO (16.0 / 9.0)

#include <stdlib.h>

int main(int argc, char **argv) {
    t_error err;
    t_camera_specs specs;
    t_scene scene;
    t_camera camera;
    t_renderer renderer;

    if (argc != 2)
    {
        log_error(E_BAD_PROGRAM_USAGE);
        return (EXIT_FAILURE);
    }
    err = parse_from_file(argv[1], &specs, &scene);
    if (err != NO_ERROR)
    {
        log_error(err);
        return (EXIT_FAILURE);
    }
    err = camera_new(specs, WIDTH, WIDTH / (double)ASPECT_RATIO, &camera);
    if (err != NO_ERROR)
    {
        log_error(err);
        scene_destroy(&scene);
        return (EXIT_FAILURE);
    }
    err = renderer_init_with_exit_hooks(WIDTH, ASPECT_RATIO, &renderer);
    if (err != NO_ERROR)
    {
        log_error(err);
        scene_destroy(&scene);
        return (EXIT_FAILURE);
    }
    render(&camera, &scene, &renderer);
    scene_destroy(&scene);
    renderer_destroy(&renderer);
}
