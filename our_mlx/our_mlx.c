#include "function.h"
#include "macro.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, X_SIZE, Y_SIZE, WIN_NAME);
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, X_SIZE, Y_SIZE);
	mlx->img.addr
		= mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEY)
		destroy_window(mlx);
	else if (keycode == LEFT_ARROW_KEY || keycode == RIGHT_ARROW_KEY
		|| keycode == DOWN_ARROW_KEY || keycode == UP_ARROW_KEY
		|| keycode == PAGE_UP_KEY || keycode == PAGE_DOWN_KEY)
	{
		camera_location_move(mlx, keycode);
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		make_image(mlx);
	}
	return (0);
}

int	destroy_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	delete_hittable(&mlx->world);
	exit(0);
}

void	minirt_hook(t_mlx *mlx)
{
	mlx_key_hook(mlx->win_ptr, &key_hook, mlx);
	mlx_hook(mlx->win_ptr, DESTROY_ICON, 0, &destroy_window, mlx);
}
