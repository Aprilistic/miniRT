/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:09:39 by taeypark          #+#    #+#             */
/*   Updated: 2023/03/02 19:42:11 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "macro.h"
#include "struct.h"

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
	if (errno == ACCESS)
		print_error("\t: failed to open the file\n");
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	int		errno;

	if (argc != 2)
	{
		print_error("Error\n\t: wrong argument count\n");
		return (0);
	}
	errno = OK;
	if (check_filename(argv[1], &errno) != OK
		|| parse(argv[1], &mlx, &errno) != OK)
	{
		print_explicit_error(errno);
		return (0);
	}
	init_mlx(&mlx);
	make_image(&mlx);
	minirt_hook(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
