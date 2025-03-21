#include "t_renderer.h"

void renderer_put_pixel(t_renderer* self,
                               size_t x,
                               size_t y,
                               uint32_t color) {
    char* dst =
        self->addr + (y * self->line_length + x * (self->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
