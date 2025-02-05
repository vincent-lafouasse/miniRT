#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

static int key_hook(int keycode, void* mlx);
static int exit_hook(void* mlx);

int main(void) {
    void* mlx = mlx_init();
    void* window = mlx_new_window(mlx, 600, 400, "miniRT");

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
