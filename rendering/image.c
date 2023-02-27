#include "function.h"
#include "macro.h"
#include "struct.h"

int	create_rgb(t_color color)
{
	limit_color_brightness(&color);
	return ((int)color.e[0] << 16 | (int)color.e[1] << 8 | (int)color.e[2]);
}

void	make_image(t_mlx *mlx)
{
	t_vec3	u;
	t_vec3	v;
	int		x;
	int		y;
	t_ray	pixel;

	u = v_unit(v_cross(v_init(0, 1, 0), mlx->camera.dir));
	v = v_unit(v_cross(mlx->camera.dir, u));
	y = -1;
	while (++y < Y_SIZE)
	{
		x = -1;
		while (++x < X_SIZE)
		{
			pixel.origin = mlx->camera.origin;
			pixel.dir =
				v_add(focal_vector(&mlx->camera), cam_offset_vector(&u, &v, x, y));
			pixel.dir = v_unit(pixel.dir);
			my_mlx_pixel_put(
				&mlx->img, x, Y_SIZE - y, create_rgb(ray_color(pixel,
						&mlx->world, REFLECTION_CNT)));
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
}
