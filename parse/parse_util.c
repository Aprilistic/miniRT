/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:34:57 by taeypark          #+#    #+#             */
/*   Updated: 2023/03/02 19:39:45 by taeypark         ###   ########.fr       */
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

void	parse_ambient(char **splited_line, t_mlx *mlx
						, int *errno, int *cap_cnt)
{
	static int	was_here;
	int			str_cnt;
	double		ambient_ratio;

	str_cnt = 0;
	while (splited_line[str_cnt])
		str_cnt++;
	if (was_here == 1 || str_cnt != 3)
	{
		*errno |= (str_cnt != 3) * OPTION_CNT;
		*errno |= (was_here == 1) * CAPITAL;
		return ;
	}
	(*cap_cnt)++;
	was_here = 1;
	ambient_ratio = atod(splited_line[1], errno);
	mlx->world.ambiance = parse_three_double(splited_line[2], errno);
	check_rgb(&mlx->world.ambiance, errno);
	check_ratio(ambient_ratio, errno);
	if (*errno == OK)
		mlx->world.ambiance = v_mul_scalar(mlx->world.ambiance, ambient_ratio);
}

void	parse_camera(char **splited_line, t_mlx *mlx
						, int *errno, int *cap_cnt)
{
	static int	was_here;
	int			str_cnt;

	str_cnt = 0;
	while (splited_line[str_cnt])
		str_cnt++;
	if (was_here == 1 || str_cnt != 4)
	{
		*errno |= (str_cnt != 4) * OPTION_CNT;
		*errno |= (was_here == 1) * CAPITAL;
		return ;
	}
	(*cap_cnt)++;
	was_here = 1;
	mlx->camera.origin = parse_three_double(splited_line[1], errno);
	mlx->camera.dir = parse_three_double(splited_line[2], errno);
	mlx->camera.fov = atod(splited_line[3], errno);
	*errno |= (v_length(mlx->camera.dir) != 1) * UNIT;
	*errno |= !(0 <= mlx->camera.fov && mlx->camera.fov <= 180) * FOV;
	if (*errno == OK)
	{
		mlx->camera.u = v_unit(v_cross(v_init(0, 1, 0), mlx->camera.dir));
		mlx->camera.v = v_unit(v_cross(mlx->camera.dir, mlx->camera.u));
	}
}

void	parse_light(char **splited_line, t_mlx *mlx
						, int *errno, int *cap_cnt)
{
	static int	was_here;
	int			str_cnt;
	t_light		light;
	double		brightness;

	str_cnt = 0;
	while (splited_line[str_cnt])
		str_cnt++;
	if (/* was_here == 1 || */str_cnt != 4)
	{
		*errno |= OPTION_CNT;
		return ;
	}
	(*cap_cnt) = (*cap_cnt);
	was_here = 1;
	light.origin = parse_three_double(splited_line[1], errno);
	brightness = atod(splited_line[2], errno);
	light.color = parse_three_double(splited_line[3], errno);
	check_rgb(&light.color, errno);
	check_ratio(brightness, errno);
	if (*errno == OK)
	{
		light.color = v_mul_scalar(light.color, brightness);
		add_light_hittable(&mlx->world, light);
	}
}

void	parse_background(char **splited_line, t_mlx *mlx
						, int *errno, int *cap_cnt)
{
	static int	was_here;
	int			str_cnt;

	str_cnt = 0;
	while (splited_line[str_cnt])
		str_cnt++;
	if (was_here == 1 || str_cnt != 2)
	{
		*errno |= (str_cnt != 2) * OPTION_CNT;
		*errno |= (was_here == 1) * CAPITAL;
		return ;
	}
	(*cap_cnt)++;
	was_here = 1;
	mlx->world.background = parse_three_double(splited_line[1], errno);
	check_rgb(&mlx->world.background, errno);
}
