/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:36:14 by jinheo            #+#    #+#             */
/*   Updated: 2023/03/02 19:36:21 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "macro.h"
#include "struct.h"
#include <unistd.h>

int	create_rgb(t_color color)
{
	limit_color_brightness(&color);
	return ((int)color.e[0] << 16 | (int)color.e[1] << 8 | (int)color.e[2]);
}

double	degree_to_radian(double degree)
{
	return (degree * PI / 180);
}

t_vec3	cam_offset_vector(t_mlx *mlx, double factor, int x, int y)
{
	double	x_scale;
	double	y_scale;
	t_vec3	x_dir;
	t_vec3	y_dir;

	x_scale = factor * (x * 2 - X_SIZE);
	y_scale = factor * (y * 2 - Y_SIZE);
	x_dir = v_mul_scalar(mlx->camera.u, x_scale);
	y_dir = v_mul_scalar(mlx->camera.v, y_scale);
	return (v_add(x_dir, y_dir));
}

void	make_image(t_mlx *mlx)
{
	int		x;
	int		y;
	t_ray	pixel;
	double	factor;

	factor = tan(degree_to_radian(mlx->camera.fov / 2.0)) / X_SIZE;
	y = -1;
	while (++y < Y_SIZE)
	{
		x = -1;
		while (++x < X_SIZE)
		{
			pixel.origin = mlx->camera.origin;
			pixel.dir = v_add(mlx->camera.dir,
					cam_offset_vector(mlx, factor, x, y));
			pixel.dir = v_unit(pixel.dir);
			my_mlx_pixel_put(
				&mlx->img, x, Y_SIZE - 1 - y, create_rgb(ray_color(pixel,
						&mlx->world, REFLECTION_CNT)));
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
}
