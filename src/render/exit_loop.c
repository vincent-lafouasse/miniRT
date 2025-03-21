#include "./t_renderer.h"

#include <mlx.h>
#include <X11/X.h>

int key_hook(int keycode, void* mlx);
int exit_hook(void* mlx);

void renderer_set_exit_loop_on_esc(t_renderer* self)
{
	mlx_key_hook(self->window, key_hook, self->mlx);
}

void renderer_set_exit_loop_on_cross(t_renderer* self)
{
	mlx_hook(self->window, DestroyNotify, StructureNotifyMask, exit_hook,
		self->mlx);

}
