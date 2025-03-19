#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

#include "parser/parse.h"
#include "scene/objects/t_hittable.h"

#define BALLS \
    "C  0,0,0       0,0,-1  90      \n" \
    "A  0.50        255,255,255     \n" \
    "L  5,4,0       0.42    255,255,255\n" \
    "sp 0,0,-1      0.5       2,62,138\n"


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
static unsigned int Color(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}

static unsigned int fColor(double r, double g, double b) {
    int r_byte = r * 255.999;
    int g_byte = g * 255.999;
    int b_byte = b * 255.999;
    return Color(r_byte, g_byte, b_byte);
}

static void draw_gradient(Image* image) {
    for (int x = 0; x < image->sz.x; x++) {
        for (int y = 0; y < image->sz.y; y++) {
            double r = (double)x / (double)image->sz.x;
            double g = 0.0;
            double b = (double)y / (double)image->sz.y;

            unsigned int color = fColor(r, g, b);
            image_put_pixel(image, (Point2){.x = x, .y = y}, color);
        }
    }
}

static int key_hook(int keycode, void* mlx);
static int exit_hook(void* mlx);

t_rgb pixel_color(Point2 px, Point2 sz, const t_camera* camera, const t_scene* scene) {
    t_point3 pixel = vec3_add(
        vec3_add(camera->pixel00, vec3_mul((double)px.x, camera->delta_u)),
        vec3_mul((double)px.y, camera->delta_v)
        );
    t_vec3 ray_direction = vec3_sub(pixel, camera->position);

    t_sphere sphere = scene->objects->data[0].sphere;
    bool hit = sphere_hit(sphere, camera->position, ray_direction);

    return hit ? vec3_new(1, 0, 0) : vec3_new(0, 0, 0);
}

void render(const t_camera* camera, const t_scene* scene, Image* screen,
t_rgb (*coloring)(Point2, Point2, const t_camera*, const t_scene*)
    ) {
    for (int x = 0; x < screen->sz.x; x++) {
        for (int y = 0; y < screen->sz.y; y++) {
            Point2 pixel = (Point2){.x = x, .y = y};
            t_rgb color = (*coloring)(pixel, screen->sz, camera, scene);
            image_put_pixel(screen, (Point2){.x = x, .y = y}, rgb_to_bytes(color));
        }
    }
}

int main(void) {
    const Point2 sz = (Point2){.x = 600, .y = 400};
    void* mlx = mlx_init();
    void* window = mlx_new_window(mlx, sz.x, sz.y, "miniRT");

    Image screen = image_new(sz, mlx);

    t_camera_specs specs;
    t_scene scene;
    parse(BALLS, &specs, &scene);
    t_camera camera = camera_new(specs, sz.x, sz.y);

    render(&camera, &scene, &screen, pixel_color);

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
