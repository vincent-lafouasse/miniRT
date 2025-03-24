#pragma once

#include "error/t_error.h"

#include <stddef.h>
#include <stdint.h>

typedef struct s_renderer t_renderer;
struct s_renderer {
    void* mlx;
    void* window;
    void* img;
    char* addr;
    size_t height;
    size_t width;
    int bits_per_pixel;
    int line_length;
    int endian;
};

t_error renderer_init(size_t width, double aspect_ratio, t_renderer *out);
t_error renderer_init_with_exit_hooks(size_t width, double aspect_ratio, t_renderer *out);
t_error renderer_from_dimensions(size_t width, size_t height, t_renderer *out);

void renderer_put_pixel(t_renderer* self,
                               size_t x,
                               size_t y,
                               uint32_t color);
void renderer_flush_pixels(t_renderer* self);

void renderer_set_exit_loop_on_esc(t_renderer* self);
void renderer_set_exit_loop_on_cross(t_renderer* self);

void renderer_enter_loop(t_renderer *self);

void renderer_destroy(t_renderer *self);
