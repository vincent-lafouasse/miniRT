#include "t_renderer.h"

t_renderer renderer_init(size_t width, double aspect_ratio) {
    t_renderer out;

    out.height = (double)width / aspect_ratio;
    out.width = width;
    out.mlx = mlx_init();
    out.window = mlx_new_window(out.mlx, width, out.height, "miniRT");
    out.img = mlx_new_image(out.mlx, width, out.height);
    out.addr = mlx_get_data_addr(out.img, &out.bits_per_pixel,
                                   &out.line_length, &out.endian);
    return out;
}
