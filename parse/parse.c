/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:35:09 by taeypark          #+#    #+#             */
/*   Updated: 2023/03/03 22:10:15 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "macro.h"
#include "function.h"

void	check_rgb(t_color *color, int *errno)
{
	if (!(0 <= color->e[0] && color->e[0] <= 255)
		|| !(0 <= color->e[1] && color->e[1] <= 255)
		|| !(0 <= color->e[2] && color->e[2] <= 255))
		*errno |= RGB;
}

void	free_two_dimension(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

int	parse_object(char *line, t_mlx *mlx, int *errno, int *cap_cnt)
{
	char	**splited_line;

	splited_line = ft_split(line, S_SPACES);
	if (ft_strcmp(splited_line[0], S_AMBIENT) == OK)
		parse_ambient(splited_line, mlx, errno, cap_cnt);
	else if (ft_strcmp(splited_line[0], S_CAMERA) == OK)
		parse_camera(splited_line, mlx, errno, cap_cnt);
	else if (ft_strcmp(splited_line[0], S_LIGHT) == OK)
		parse_light(splited_line, mlx, errno, cap_cnt);
	else if (ft_strcmp(splited_line[0], S_BACK) == OK)
		parse_background(splited_line, mlx, errno, cap_cnt);
	else if (ft_strcmp(splited_line[0], S_SPHERE) == OK)
		parse_sphere(splited_line, mlx, errno);
	else if (ft_strcmp(splited_line[0], S_PLANE) == OK)
		parse_plane(splited_line, mlx, errno);
	else if (ft_strcmp(splited_line[0], S_CYLINDER) == OK)
		parse_cylinder(splited_line, mlx, errno);
	else if (ft_strcmp(splited_line[0], "#") != OK)
		*errno |= UNDEFINED;
	free_two_dimension(splited_line);
	return (*errno);
}

int	parse(char *file, t_mlx *mlx, int *errno)
{
	int		fd;
	int		cap_cnt;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == ERROR || read(fd, NULL, 0) == ERROR)
		return (ERROR);
	cap_cnt = 0;
	init_hittable(&mlx->world);
	while (*errno == OK)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '\n'
			&& parse_object(line, mlx, errno, &cap_cnt) != OK)
			delete_hittable(&mlx->world);
		free(line);
	}
	close(fd);
	if (*errno == OK && cap_cnt != CAP_CNT)
		*errno |= CAPITAL;
	return (*errno);
}
