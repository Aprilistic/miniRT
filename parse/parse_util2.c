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
	parse_commons(&object, splited_line, errno, 3);
	object.type = PLANE;
	object.equation = plane;
	check_rgb(&object.surface.color, errno);
	*errno |= (v_length(plane->normal) != 1) * UNIT;
	if (*errno == OK)
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
	cylinder->dir_vector = parse_three_double(splited_line[2], errno);
	cylinder->diameter = atod(splited_line[3], errno);
	cylinder->height = atod(splited_line[4], errno);
	parse_commons(&object, splited_line, errno, 5);
	object.type = CYLINDER;
	object.equation = cylinder;
	check_rgb(&object.surface.color, errno);
	*errno |= (cylinder->diameter < 0 || cylinder->height < 0) * LENGTH;
	*errno |= (v_length(cylinder->dir_vector) != 1) * UNIT;
	if (*errno == OK)
		add_object_hittable(&mlx->world, object);
}

void	parse_cone(char **splited_line, t_mlx *mlx, int *errno)
{
	t_object		object;
	t_cone			*cone;
	int				field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	if (field_cnt != ARG_CNT)
	{
		*errno |= OPTION_CNT;
		return ;
	}
	cone = malloc(sizeof(t_cone));
	cone->center = parse_three_double(splited_line[1], errno);
	cone->coefficient = parse_three_double(splited_line[2], errno);
	object.surface.color = parse_three_double(splited_line[3], errno);
	parse_commons(&object, splited_line, errno, 4);
	object.type = CONE;
	object.equation = cone;
	check_rgb(&object.surface.color, errno);
	add_object_hittable(&mlx->world, object);
}
