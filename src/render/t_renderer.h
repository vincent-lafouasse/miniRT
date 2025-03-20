#pragma once

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

t_renderer renderer_init(size_t width, double aspect_ratio);
t_renderer renderer_from_dimensions(size_t width, size_t height);
void renderer_put_pixel(t_renderer* renderer,
                               size_t x,
                               size_t y,
                               uint32_t color);
