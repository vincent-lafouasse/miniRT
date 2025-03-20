#include "t_renderer.h"

#include "error/t_error.h"

#include "mlx.h"
#include <stddef.h>

t_error renderer_init(size_t width, double aspect_ratio, t_renderer *out) {
    const size_t height = (double)width / aspect_ratio;

    return renderer_from_dimensions(width, height, out);
}

t_error renderer_from_dimensions(size_t width, size_t height, t_renderer *out) {
    t_renderer r;

    r = (t_renderer){.height = height, .width = width, 0};
    r.mlx = mlx_init();
    if (!r.mlx)
        return (E_OOM);
    r.window = mlx_new_window(r.mlx, width, r.height, "miniRT");
    if (!r.window)
    {
        renderer_destroy(&r);
        return (E_OOM);
    }
    r.img = mlx_new_image(r.mlx, width, r.height);
    if (!r.img)
    {
        renderer_destroy(&r);
        return (E_OOM);
    }
    r.addr = mlx_get_data_addr(r.img, &r.bits_per_pixel,
                                   &r.line_length, &r.endian);
    *out = r;
    return (NO_ERROR);
}
