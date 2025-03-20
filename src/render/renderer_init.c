#include "t_renderer.h"

#include "mlx.h"

t_renderer renderer_init(size_t width, double aspect_ratio) {
    const size_t height = (double)width / aspect_ratio;

    return renderer_from_dimensions(width, height);
}

t_renderer renderer_from_dimensions(size_t width, size_t height) {
    t_renderer out;

    out.height = height;
    out.width = width;
    out.mlx = mlx_init();
    out.window = mlx_new_window(out.mlx, width, out.height, "miniRT");
    out.img = mlx_new_image(out.mlx, width, out.height);
    out.addr = mlx_get_data_addr(out.img, &out.bits_per_pixel,
                                   &out.line_length, &out.endian);
    return out;
}
