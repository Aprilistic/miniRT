/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:09:39 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/22 19:10:34 by taeypark         ###   ########.fr       */
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
			my_mlx_pixel_put(&mlx->img, x, y, 0x00FFFFFF);
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

void	print_three_doubles(t_vec3 *num)
{
	printf("%lf,%lf,%lf\n", num->e[0], num->e[1], num->e[2]);
}

void	print_object(t_object *object)
{
	if (object->type == SPHERE)
	{
		printf("sphere. \n");
		printf("center : ");
		print_three_doubles(&((t_sphere *)object->equation)->center);
		printf("diameter : %lf\n\n", ((t_sphere *)object->equation)->diameter);
	}
	else if (object->type == CYLINDER)
	{
		printf("cylider. \n");
		printf("point : ");
		print_three_doubles(&((t_cylinder *)object->equation)->point);
		printf("dir : ");
		print_three_doubles(&((t_cylinder *)object->equation)->dir_vector);
		printf("height : ");
		printf("%lf\n", ((t_cylinder *)object->equation)->height);
		printf("diameter : ");
		printf("%lf\n\n", ((t_cylinder *)object->equation)->diameter);
	}
	else if (object->type == CONE)
	{
		printf("cone. \n");
		printf("center : ");
		print_three_doubles(&((t_cone *)object->equation)->center);
		printf("coefficient : ");
		print_three_doubles(&((t_cone *)object->equation)->coefficient);
		printf("\n");
	}
	else if (object->type == PLANE)
	{
		printf("plane. \n");
		printf("point : ");
		print_three_doubles(&((t_plane *)object->equation)->point);
		printf("dir_vector : ");
		print_three_doubles(&((t_plane *)object->equation)->dir_vector);
		printf("\n");
	}
}

void	debug_parsing(t_mlx *mlx)
{
	printf("=== camera ===\n");
	printf("dir : ");
	print_three_doubles(&mlx->camera.dir);
	printf("origin : ");
	print_three_doubles(&mlx->camera.origin);
	printf("fov : %d\n", mlx->fov);
	printf("=================\n\n");
	
	printf("=== light ===\n");
	for (int i = 0; i < mlx->world.cur_light_count; i++)
	{
		printf("%d. \n", i + 1);
		printf("origin : ");
		print_three_doubles(&mlx->world.light->origin);
		printf("color : ");
		print_three_doubles(&mlx->world.light->color);
	}
	printf("=================\n\n");

	printf("=== objects ===\n");
	for (int i = 0; i < mlx->world.cur_object_count; i++)
		print_object(&mlx->world.object[i]);
	printf("=================\n\n");
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
	{
		write(2, "argc Error\n", 11);
		return (0);
	}

	// parse .rt file
	if (check_filename(argv[1]) == ERROR || parse(argv[1], &mlx) == ERROR)
	{
		write(2, ".rt Error\n", 10);
		return (0);
	}

	// debug parsing part
	debug_parsing(&mlx);

	// make ray tracing!
	init_mlx(&mlx);
	make_ray_tracing(&mlx);

	// mlx_loop()!
	minirt_hook(&mlx);
	mlx_loop(mlx.mlx_ptr);

	return (0);
}
