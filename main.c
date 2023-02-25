/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:09:39 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/25 21:21:04 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "macro.h"
#include "struct.h"

int	check_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if ((len >= 3) && (filename[len - 3] == '.' && filename[len - 2] == 'r'
			&& filename[len - 1] == 't'))
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
		printf("* sphere *\n");
		printf("center : ");
		print_three_doubles(&((t_sphere *)object->equation)->center);
		printf("diameter : %lf\n", ((t_sphere *)object->equation)->diameter);
	}
	else if (object->type == CYLINDER)
	{
		printf("* cylider *\n");
		printf("point : ");
		print_three_doubles(&((t_cylinder *)object->equation)->point);
		printf("dir : ");
		print_three_doubles(&((t_cylinder *)object->equation)->dir_vector);
		printf("height : ");
		printf("%lf\n", ((t_cylinder *)object->equation)->height);
		printf("diameter : ");
		printf("%lf\n", ((t_cylinder *)object->equation)->diameter);
	}
	else if (object->type == CONE)
	{
		printf("* cone *\n");
		printf("center : ");
		print_three_doubles(&((t_cone *)object->equation)->center);
		printf("coefficient : ");
		print_three_doubles(&((t_cone *)object->equation)->coefficient);
	}
	else if (object->type == PLANE)
	{
		printf("* plane *\n");
		printf("point : ");
		print_three_doubles(&((t_plane *)object->equation)->point);
		printf("dir_vector : ");
		print_three_doubles(&((t_plane *)object->equation)->normal);
	}
	printf("checkerboard : %d\n", object->surface.checkerboard);
	printf("diffuse_rate : %f\n", object->surface.diffuse_rate);
	printf("specular_rate : %f\n", object->surface.specular_rate);
	printf("brightness_rate : %f\n\n", object->surface.brightness_rate);
}

void	debug_parsing(t_mlx *mlx)
{
	printf("=== camera ===\n");
	printf("dir : ");
	print_three_doubles(&mlx->camera.dir);
	printf("origin : ");
	print_three_doubles(&mlx->camera.origin);
	printf("fov : %d\n", mlx->camera.fov);
	printf("=================\n\n");

	printf("=== ambiance ===\n");
	print_three_doubles(&mlx->world.ambiance);
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

void	print_error(char *msg)
{
	int	len;

	len = ft_strlen(msg);
	write(2, msg, len);
}

void	leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	// atexit(leaks);
	if (argc != 2)
	{
		print_error("Error: wrong argument count\n");
		return (0);
	}
	// parse .rt file
	if (check_filename(argv[1]) == ERROR || parse(argv[1], &mlx) == ERROR)
	{
		print_error("Error: wrong .rt file\n");
		return (0);
	}
	// debug parsing part
	debug_parsing(&mlx);
	// make ray tracing!
	init_mlx(&mlx);
	make_image(&mlx);
	// mlx_loop()!
	minirt_hook(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
