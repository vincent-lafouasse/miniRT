#include "t_renderer.h"

void renderer_put_pixel(t_renderer* renderer,
                               size_t x,
                               size_t y,
                               uint32_t color) {
    char* dst = renderer->addr + (y * renderer->line_length +
                                  x * (renderer->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
