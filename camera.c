#include "function.h"
#include "macro.h"
#include "struct.h"
#include <math.h>
#include <sys/signal.h>

t_vec3	focal_vector(t_camera *camera)
{
	t_vec3	dir;

	dir = v_unit(camera->dir);
	dir = v_mul_scalar(dir, asin(camera->fov / 2.0) * X_SIZE / 2
			* cos(camera->fov / 2.0));
	return (dir);
}

t_vec3	cam_offset_vector(t_vec3 *u, t_vec3 *v, int x, int y)
{
	t_vec3	x_dir;
	t_vec3	y_dir;

	x_dir = v_mul_scalar(*u, x - X_SIZE);
	y_dir = v_mul_scalar(*v, y - Y_SIZE);
	return (v_add(x_dir, y_dir));
}

int	create_rgb(t_color color)
{
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
			pixel.dir = v_add(focal_vector(&mlx->camera),
					cam_offset_vector(&u, &v, x, y));
			pixel.dir = v_unit(pixel.dir);
			my_mlx_pixel_put(&mlx->img, x, y, create_rgb(ray_color(pixel,
						&mlx->world, REFLECTION_CNT)));
		}
	}
}
