#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

typedef struct {
    int x;
    int y;
} Point2;

typedef struct {
    void* img;
    char* addr;
    Point2 sz;
    int bits_per_pixel;
    int line_length;
    int endian;
} Image;

static Image image_new(Point2 sz, void* mlx);
static void image_put_pixel(Image* img, Point2 position, int color);

static int key_hook(int keycode, void* mlx);
static int exit_hook(void* mlx);

int main(void) {
    const Point2 sz = (Point2){.x = 600, .y = 400};
    void* mlx = mlx_init();
    void* window = mlx_new_window(mlx, sz.x, sz.y, "miniRT");

    Image screen = image_new(sz, mlx);
    image_put_pixel(&screen, (Point2){.x = 100, .y = 20}, 0x00FF0000);
    mlx_put_image_to_window(mlx, window, screen.img, 0, 0);

    mlx_hook(window, DestroyNotify, StructureNotifyMask, exit_hook, mlx);
    mlx_key_hook(window, &key_hook, mlx);
    mlx_loop(mlx);
}

static int key_hook(int keycode, void* mlx) {
    if (keycode == XK_Escape)
        mlx_loop_end(mlx);
    return (0);
}

static int exit_hook(void* mlx) {
    mlx_loop_end(mlx);
    return (0);
}

static Image image_new(Point2 sz, void* mlx) {
    Image image;

    image.img = mlx_new_image(mlx, sz.x, sz.y);
    image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
                                   &image.line_length, &image.endian);
    image.sz = sz;
    return image;
}

static void image_put_pixel(Image* img, Point2 position, int color) {
    char* dst = img->addr + (position.y * img->line_length +
                             position.x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
