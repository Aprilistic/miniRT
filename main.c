/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:09:39 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/27 19:51:03 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "macro.h"
#include "struct.h"

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
		print_three_doubles(&((t_cylinder *)object->equation)->center);
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

int	check_filename(char *filename, int *errno)
{
	int	len;

	len = ft_strlen(filename);
	if ((len >= 3) && (filename[len - 3] == '.' && filename[len - 2] == 'r'
			&& filename[len - 1] == 't'))
		return (OK);
	*errno |= EXTENSION;
	return (*errno);
}

void	print_explicit_error(int errno)
{
	print_error("Error\n");
	if (errno & EXTENSION)
		print_error("\t: not a .rt file\n");
	if (errno & LENGTH)
		print_error("\t: length should be positive\n");
	if (errno & FOV)
		print_error("\t: fov should be 0~180\n");
	if (errno & RATE)
		print_error("\t: ratio should be 0~1\n");
	if (errno & UNIT)
		print_error("\t: not a unit vector\n");
	if (errno & RGB)
		print_error("\t: rgb should be 0~255\n");
	if (errno & UNDEFINED)
		print_error("\t: undefined identifier\n");
	if (errno & OPTION_CNT)
		print_error("\t: wrong option count\n");
	if (errno & NUM)
		print_error("\t: number error\n");
	if (errno & CAPITAL)
		print_error("\t: capital identifier count error\n");
	if (errno == 0)
		print_error("\t: failed to open the file\n");
}

void	leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	int		errno;

	// atexit(leaks);
	if (argc != 2)
	{
		print_error("Error\n\t: wrong argument count\n");
		return (0);
	}
	// parse .rt file
	errno = OK;
	if (check_filename(argv[1], &errno) != OK
		|| parse(argv[1], &mlx, &errno) != OK)
	{
		print_explicit_error(errno);
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
