#include "mlx.h"

#include <X11/keysym.h>

int key_hook(int keycode, void* mlx) {
    if (keycode == XK_Escape)
        mlx_loop_end(mlx);
    return (0);
}

int exit_hook(void* mlx) {
    mlx_loop_end(mlx);
    return (0);
}
