
#include "../includes/main.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, X_SIZE, Y_SIZE, WIN_NAME);
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, X_SIZE, Y_SIZE);
	mlx->img.addr
		= mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel
			, &mlx->img.line_length, &mlx->img.endian);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
