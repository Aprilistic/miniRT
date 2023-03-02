/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:36:04 by jinheo            #+#    #+#             */
/*   Updated: 2023/03/02 19:36:10 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "macro.h"
#include "struct.h"
#include <math.h>

void	camera_location_move(t_mlx *mlx, int keycode)
{
	t_vec3	*cam_location;
	t_vec3	horizontal_dir;
	t_vec3	vertical_dir;

	cam_location = &mlx->camera.origin;
	horizontal_dir = v_cross(v_init(0, 1, 0), mlx->camera.dir);
	horizontal_dir = v_unit(horizontal_dir);
	vertical_dir = v_cross(mlx->camera.dir, horizontal_dir);
	vertical_dir = v_unit(vertical_dir);
	if (keycode == LEFT_ARROW_KEY)
		*cam_location = v_sub(*cam_location, horizontal_dir);
	else if (keycode == RIGHT_ARROW_KEY)
		*cam_location = v_add(*cam_location, horizontal_dir);
	else if (keycode == DOWN_ARROW_KEY)
		*cam_location = v_sub(*cam_location, mlx->camera.dir);
	else if (keycode == UP_ARROW_KEY)
		*cam_location = v_add(*cam_location, mlx->camera.dir);
	else if (keycode == PAGE_UP_KEY)
		*cam_location = v_add(*cam_location, vertical_dir);
	else if (keycode == PAGE_DOWN_KEY)
		*cam_location = v_sub(*cam_location, vertical_dir);
}

int	camera_fov_change(t_mlx *mlx, int keycode)
{
	if (keycode == SCROLL_UP)
	{
		if (mlx->camera.fov >= 180)
			return (0);
		mlx->camera.fov += 5;
	}
	else if (keycode == SCROLL_DOWN)
	{
		if (mlx->camera.fov <= 0)
			return (0);
		mlx->camera.fov -= 5;
	}
	if (mlx->camera.fov > 180)
		mlx->camera.fov = 180;
	else if (mlx->camera.fov < 0)
		mlx->camera.fov = 0;
	return (1);
}
