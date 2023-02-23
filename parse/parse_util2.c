#include "struct.h"
#include "macro.h"
#include "function.h"
#include <stdlib.h>
#include <fcntl.h>
#define ARG_CNT 4

// sp   0.0,0.0,20.6   12.6    10,0,255
void	parse_sphere(char **splited_line, t_mlx *mlx, int *status)
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
		*status = ERROR;
		return ;
	}

	sphere = malloc(sizeof(t_sphere));
	sphere->center = parse_three_double(splited_line[1], status);
	sphere->diameter = atod(splited_line[2], status);
	object.surface.color = parse_three_double(splited_line[3], status);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// object.surface.checkerboard = (atod(splited_line[4], status) != 0);
	// object.surface.diffuse_rate = atod(splited_line[5], status);
	// object.surface.specular_rate = atod(splited_line[6], status);
	// object.surface.brightness_rate = atod(splited_line[7], status);

	// 드디어 list에 넣기!!!
	object.type = SPHERE;
	object.equation = sphere;
	if (sphere->diameter < 0
		|| check_rgb(&object.surface.color) == ERROR)
		*status = ERROR;
	else if (sphere->diameter > 0)
		add_object_hittable(&mlx->world, object);
}

// pl     0.0,0.0,-10.0    0.0,1.0,0.0   0,0,255
void	parse_plane(char **splited_line, t_mlx *mlx, int *status)
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
		*status = ERROR;
		return ;
	}

	plane = malloc(sizeof(t_plane));
	plane->point = parse_three_double(splited_line[1], status);
	plane->normal = parse_three_double(splited_line[2], status);
	object.surface.color = parse_three_double(splited_line[3], status);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// object.surface.checkerboard = (atod(splited_line[4], status) != 0);
	// object.surface.diffuse_rate = atod(splited_line[5], status);
	// object.surface.specular_rate = atod(splited_line[6], status);
	// object.surface.brightness_rate = atod(splited_line[7], status);

	// 드디어 list에 넣기!!!
	object.type = PLANE;
	object.equation = plane;
	add_object_hittable(&mlx->world, object);
	if (v_length(plane->normal) != 1
		|| check_rgb(&object.surface.color) == ERROR)
		*status = ERROR;
}

// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
void	parse_cylinder(char **splited_line, t_mlx *mlx, int *status)
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
		*status = ERROR;
		return ;
	}

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->point = parse_three_double(splited_line[1], status);
	cylinder->dir_vector = parse_three_double(splited_line[2], status);
	cylinder->diameter = atod(splited_line[3], status);
	cylinder->height = atod(splited_line[4], status);
	object.surface.color = parse_three_double(splited_line[5], status);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// object.surface.checkerboard = (atod(splited_line[5], status) != 0);
	// object.surface.diffuse_rate = atod(splited_line[6], status);
	// object.surface.specular_rate = atod(splited_line[7], status);
	// object.surface.brightness_rate = atod(splited_line[8], status);

	// 드디어 list에 넣기!!!
	object.type = CYLINDER;
	object.equation = cylinder;
	add_object_hittable(&mlx->world, object);
	if (cylinder->diameter < 0 || v_length(cylinder->dir_vector) != 1
		|| cylinder->height < 0 || check_rgb(&object.surface.color) == ERROR)
		*status = ERROR;
}

void	parse_cone(char **splited_line, t_mlx *mlx, int *status)
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
		*status = ERROR;
		return ;
	}

	cone = malloc(sizeof(t_cone));
	cone->center = parse_three_double(splited_line[1], status);
	cone->coefficient = parse_three_double(splited_line[2], status);
	object.surface.color = parse_three_double(splited_line[3], status);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// object.surface.checkerboard = (atod(splited_line[5], status) != 0);
	// object.surface.diffuse_rate = atod(splited_line[6], status);
	// object.surface.specular_rate = atod(splited_line[7], status);
	// object.surface.brightness_rate = atod(splited_line[8], status);

	// 드디어 list에 넣기!!!
	object.type = CONE;
	object.equation = cone;
	add_object_hittable(&mlx->world, object);
	if (check_rgb(&object.surface.color) == ERROR)
		*status = ERROR;
}
