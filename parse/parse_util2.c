#include "struct.h"
#include "macro.h"
#include "function.h"

// sp   0.0,0.0,20.6   12.6    10,0,255
void	parse_sphere(char **splited_line, t_mlx *mlx, int *errno)
{
	t_object	object;
	t_sphere	*sphere;
	int			field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	// 아직은 옵션 처리 안 함
	if (field_cnt != ARG_CNT)
	{
		*errno |= OPTION_CNT;
		return ;
	}

	sphere = malloc(sizeof(t_sphere));
	sphere->center = parse_three_double(splited_line[1], errno);
	sphere->diameter = atod(splited_line[2], errno);
	object.surface.color = parse_three_double(splited_line[3], errno);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	object.surface.diffuse_rate = atod(splited_line[4], errno);
	object.surface.specular_rate = atod(splited_line[5], errno);
	object.surface.brightness_rate = atod(splited_line[6], errno);

	// 드디어 list에 넣기!!!
	object.type = SPHERE;
	object.equation = sphere;
	check_rgb(&object.surface.color, errno);
	if (sphere->diameter < 0)
		*errno |= LENGTH;
	else if (sphere->diameter > 0)
		add_object_hittable(&mlx->world, object);
}

// pl     0.0,0.0,-10.0    0.0,1.0,0.0   0,0,255
void	parse_plane(char **splited_line, t_mlx *mlx, int *errno)
{
	t_object	object;
	t_plane		*plane;
	int			field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	// 아직은 옵션 처리 안 함
	if (field_cnt != ARG_CNT)
	{
		*errno |= OPTION_CNT;
		return ;
	}

	plane = malloc(sizeof(t_plane));
	plane->point = parse_three_double(splited_line[1], errno);
	plane->normal = parse_three_double(splited_line[2], errno);
	object.surface.color = parse_three_double(splited_line[3], errno);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	object.surface.diffuse_rate = atod(splited_line[4], errno);
	object.surface.specular_rate = atod(splited_line[5], errno);
	object.surface.brightness_rate = atod(splited_line[6], errno);

	// 드디어 list에 넣기!!!
	object.type = PLANE;
	object.equation = plane;
	check_rgb(&object.surface.color, errno);
	if (v_length(plane->normal) != 1)
		*errno |= UNIT;
	else
		add_object_hittable(&mlx->world, object);
}

// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
void	parse_cylinder(char **splited_line, t_mlx *mlx, int *errno)
{
	t_object		object;
	t_cylinder		*cylinder;
	int				field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	// 아직은 옵션 처리 안 함
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
	object.surface.color = parse_three_double(splited_line[5], errno);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	object.surface.diffuse_rate = atod(splited_line[5], errno);
	object.surface.specular_rate = atod(splited_line[6], errno);
	object.surface.brightness_rate = atod(splited_line[7], errno);

	// 드디어 list에 넣기!!!
	object.type = CYLINDER;
	object.equation = cylinder;
	check_rgb(&object.surface.color, errno);
	if (cylinder->diameter < 0 || cylinder->height < 0)
		*errno |= LENGTH;
	if (v_length(cylinder->dir_vector) != 1)
		*errno |= UNIT;
	else
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
	// 아직은 옵션 처리 안 함
	if (field_cnt != ARG_CNT)
	{
		*errno |= OPTION_CNT;
		return ;
	}

	cone = malloc(sizeof(t_cone));
	cone->center = parse_three_double(splited_line[1], errno);
	cone->coefficient = parse_three_double(splited_line[2], errno);
	object.surface.color = parse_three_double(splited_line[3], errno);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// object.surface.checkerboard = (atod(splited_line[5], errno) != 0);
	// object.surface.diffuse_rate = atod(splited_line[6], errno);
	// object.surface.specular_rate = atod(splited_line[7], errno);
	// object.surface.brightness_rate = atod(splited_line[8], errno);

	// 드디어 list에 넣기!!!
	object.type = CONE;
	object.equation = cone;
	check_rgb(&object.surface.color, errno);
	add_object_hittable(&mlx->world, object);
}
