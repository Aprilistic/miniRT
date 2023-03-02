/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:35:00 by taeypark          #+#    #+#             */
/*   Updated: 2023/03/02 19:41:02 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "macro.h"
#include "function.h"

void	parse_commons(t_object *object, char **splited, int *errno
						, int start_idx)
{
	object->surface.color = parse_three_double(splited[start_idx], errno);
	object->surface.diffuse_rate = atod(splited[start_idx + 1], errno);
	object->surface.specular_rate = atod(splited[start_idx + 2], errno);
	object->surface.brightness_rate = atod(splited[start_idx + 3], errno);
	check_rgb(&object->surface.color, errno);
	check_ratio(object->surface.diffuse_rate, errno);
	check_ratio(object->surface.brightness_rate, errno);
	check_ratio(object->surface.brightness_rate, errno);
}

void	parse_sphere(char **splited_line, t_mlx *mlx, int *errno)
{
	t_object	object;
	t_sphere	*sphere;
	int			field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	if (field_cnt != ARG_CNT)
	{
		*errno |= OPTION_CNT;
		return ;
	}
	sphere = malloc(sizeof(t_sphere));
	sphere->center = parse_three_double(splited_line[1], errno);
	sphere->diameter = atod(splited_line[2], errno);
	parse_commons(&object, splited_line, errno, 3);
	object.type = SPHERE;
	object.equation = sphere;
	*errno |= (sphere->diameter < 0) * LENGTH;
	if (*errno == OK)
		add_object_hittable(&mlx->world, object);
}

void	parse_plane(char **splited_line, t_mlx *mlx, int *errno)
{
	t_object	object;
	t_plane		*plane;
	int			field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	if (field_cnt != ARG_CNT)
	{
		*errno |= OPTION_CNT;
		return ;
	}
	plane = malloc(sizeof(t_plane));
	plane->point = parse_three_double(splited_line[1], errno);
	plane->normal = parse_three_double(splited_line[2], errno);
	plane->circle_shape = 0;
	parse_commons(&object, splited_line, errno, 3);
	object.type = PLANE;
	object.equation = plane;
	check_rgb(&object.surface.color, errno);
	*errno |= (v_length(plane->normal) != 1) * UNIT;
	if (*errno == OK)
		add_object_hittable(&mlx->world, object);
}

void	add_cylinder_hittable(t_mlx *mlx, t_object cylinder_obj)
{
	t_plane		*plane;
	t_object	object;
	t_cylinder	*cylinder;

	add_object_hittable(&mlx->world, cylinder_obj);
	cylinder = (t_cylinder *)cylinder_obj.equation;
	object.type = PLANE;
	object.surface = cylinder_obj.surface;
	plane = malloc(sizeof(t_plane));
	plane->circle_shape = 1;
	plane->radius = cylinder->diameter / 2;
	plane->normal = cylinder->dir;
	plane->point = v_add(cylinder->center,
			v_mul_scalar(cylinder->dir, cylinder->height / 2));
	object.equation = plane;
	add_object_hittable(&mlx->world, object);
	plane = malloc(sizeof(t_plane));
	plane->circle_shape = 1;
	plane->radius = cylinder->diameter / 2;
	plane->normal = v_mul_scalar(cylinder->dir, -1);
	plane->point = v_add(cylinder->center,
			v_mul_scalar(cylinder->dir, -cylinder->height / 2));
	object.equation = plane;
	add_object_hittable(&mlx->world, object);
}

void	parse_cylinder(char **splited_line, t_mlx *mlx, int *errno)
{
	t_object		object;
	t_cylinder		*cylinder;
	int				field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	if (field_cnt != ARG_CNT + 2)
	{
		*errno |= OPTION_CNT;
		return ;
	}
	cylinder = malloc(sizeof(t_cylinder));
	cylinder->center = parse_three_double(splited_line[1], errno);
	cylinder->dir = v_unit(parse_three_double(splited_line[2], errno));
	cylinder->diameter = atod(splited_line[3], errno);
	cylinder->height = atod(splited_line[4], errno);
	parse_commons(&object, splited_line, errno, 5);
	object.type = CYLINDER;
	object.equation = cylinder;
	check_rgb(&object.surface.color, errno);
	*errno |= (cylinder->diameter < 0 || cylinder->height < 0) * LENGTH;
	*errno |= (v_length(cylinder->dir) != 1) * UNIT;
	if (*errno == OK)
		add_cylinder_hittable(mlx, object);
}
