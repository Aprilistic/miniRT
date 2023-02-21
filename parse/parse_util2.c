#include "../struct.h"
#include "../macro.h"
#include "../function.h"
#include <stdlib.h>
#include <fcntl.h>

// sp   0.0,0.0,20.6   12.6    10,0,255
void	parse_sphere(char **splited_line, t_mlx *mlx, int *status)
{
	t_shape		shape;
	t_sphere	*sphere;
	char		*save;
	int			field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	// 아직은 옵션 처리 안 함
	if (field_cnt != 4)
	{
		*status = ERROR;
		return ;
	}

	sphere = malloc(sizeof(t_sphere));
	save = splited_line[1];
	sphere->center = parse_three_double(&save, status);
	save = splited_line[2];
	sphere->diameter = atod(&save, status);
	save = splited_line[3];
	shape.color.color = parse_three_double(&save, status);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// save = splited_line[4];
	// shape.color.checkerboard = (atod(&save, status) != 0);
	// save = splited_line[5];
	// shape.color.diffuse_rate = atod(&save, status);
	// save = splited_line[6];
	// shape.color.specular_rate = atod(&save, status);
	// save = splited_line[7];
	// shape.color.brightness_rate = atod(&save, status);

	// 드디어 list에 넣기!!!
	shape.type = SPHERE;
	shape.characteristic = sphere;
	add_to_hittable(mlx->obj_list, shape);
}

// pl     0.0,0.0,-10.0    0.0,1.0,0.0   0,0,255
void	parse_plane(char **splited_line, t_mlx *mlx, int *status)
{
	t_shape		shape;
	t_plane		*plane;
	char		*save;
	int			field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	// 아직은 옵션 처리 안 함
	if (field_cnt != 4)
	{
		*status = ERROR;
		return ;
	}

	plane = malloc(sizeof(t_plane));
	save = splited_line[1];
	plane->point = parse_three_double(&save, status);
	save = splited_line[2];
	plane->dir_vector = parse_three_double(&save, status);
	save = splited_line[3];
	shape.color.color = parse_three_double(&save, status);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// save = splited_line[4];
	// shape.color.checkerboard = (atod(&save, status) != 0);
	// save = splited_line[5];
	// shape.color.diffuse_rate = atod(&save, status);
	// save = splited_line[6];
	// shape.color.specular_rate = atod(&save, status);
	// save = splited_line[7];
	// shape.color.brightness_rate = atod(&save, status);

	// 드디어 list에 넣기!!!
	shape.type = PLANE;
	shape.characteristic = plane;
	add_to_hittable(mlx->obj_list, shape);
}

// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
void	parse_cylinder(char **splited_line, t_mlx *mlx, int *status)
{
	t_shape			shape;
	t_cylinder		*cylinder;
	char			*save;
	int				field_cnt;

	field_cnt = 0;
	while (splited_line[field_cnt])
		field_cnt++;
	// 아직은 옵션 처리 안 함
	if (field_cnt != 4)
	{
		*status = ERROR;
		return ;
	}

	cylinder = malloc(sizeof(t_cylinder));
	save = splited_line[1];
	cylinder->point = parse_three_double(&save, status);
	save = splited_line[2];
	cylinder->dir_vector = parse_three_double(&save, status);
	save = splited_line[3];
	cylinder->diameter = atod(&save, status);
	save = splited_line[4];
	cylinder->height = atod(&save, status);

	// 여기 부터 옵션 checkerboard, diffuse, specular, brightness
	// save = splited_line[4];
	// shape.color.checkerboard = (atod(&save, status) != 0);
	// save = splited_line[5];
	// shape.color.diffuse_rate = atod(&save, status);
	// save = splited_line[6];
	// shape.color.specular_rate = atod(&save, status);
	// save = splited_line[7];
	// shape.color.brightness_rate = atod(&save, status);

	// 드디어 list에 넣기!!!
	shape.type = CYLINDER;
	shape.characteristic = cylinder;
	add_to_hittable(mlx->obj_list, shape);
}

void	parse_cone(char **splited_line, t_mlx *mlx, int *status)
{
	(void)splited_line, (void)mlx, (void)status;
}
