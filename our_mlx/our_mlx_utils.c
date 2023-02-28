#include "function.h"
#include "macro.h"

int	mouse_hook(int mouse_code, int x, int y, t_mlx *mlx)
{
	x = 0;
	y = 0;
	if (mouse_code == SCROLL_UP || mouse_code == SCROLL_DOWN)
	{
		camera_fov_change(mlx, mouse_code);
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		make_image(mlx);
	}
	return (0);
}
