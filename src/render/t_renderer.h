#pragma once

#include "mlx.h"
#include <stddef.h>

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
