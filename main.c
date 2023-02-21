/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:09:39 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/21 20:31:53 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "macro.h"

void	make_ray_tracing(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < Y_SIZE)
	{
		x = 0;
		while (x < X_SIZE)
		{
			my_mlx_pixel_put(&mlx->img, y, x, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
}

int	check_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if ((len >= 3) && (filename[len - 3] == '.'
		&& filename[len - 2] == 'r' && filename[len - 1] == 't'))
		return (OK);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
	{
		write(2, "argc error\n", 11);
		return (0);
	}

	// parse .rt file
	if (check_filename(argv[1]) == ERROR || parse(argv[1], &mlx) == ERROR)
	{
		write(2, ".rt error\n", 10);
		return (0);
	}

	// make ray tracing!
	init_mlx(&mlx);
	make_ray_tracing(&mlx);

	// mlx_loop()!
	minirt_hook(&mlx);
	mlx_loop(mlx.mlx_ptr);

	return (0);
}
