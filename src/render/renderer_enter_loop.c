#include "./t_renderer.h"

#include "mlx.h"

void renderer_enter_loop(t_renderer *self)
{
	mlx_loop(self->mlx);
}
