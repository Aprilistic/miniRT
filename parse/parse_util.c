#include "struct.h"
#include "macro.h"
#include "function.h"
#include <stdlib.h>
#include <fcntl.h>

void	parse_ambient(char **splited_line, t_mlx *mlx
						, int *status, int *cap_status)
{
	static int	was_here;
	int			str_cnt;
	double		ambient_ratio;

	if (was_here == 0)
		cap_status++;
	else
	{
		*status = ERROR;
		return ;
	}
	str_cnt = 0;
	while (splited_line[str_cnt])
		str_cnt++;
	if (str_cnt != 3)
	{
		*status = ERROR;
		return ;
	}
	ambient_ratio = atod(&splited_line[0], status);
	mlx->world.ambiance
		= v_mul_scalar(parse_three_double(&splited_line[1], status)
			, ambient_ratio);
	was_here = 1;
}

void	parse_camera(char **splited_line, t_mlx *mlx
						, int *status, int *cap_status)
{
	static int	was_here;
	int			str_cnt;

	if (was_here == 0)
		cap_status++;
	else
	{
		*status = ERROR;
		return ;
	}
	str_cnt = 0;
	while (splited_line[str_cnt])
		str_cnt++;
	if (str_cnt != 4)
	{
		*status = ERROR;
		return ;
	}
	mlx->camera.origin = parse_three_double(&splited_line[1], status);
	mlx->camera.dir = parse_three_double(&splited_line[2], status);
	mlx->fov = atod(&splited_line[3], status);
	was_here = 1;
}

void	parse_light(char **splited_line, t_mlx *mlx
						, int *status, int *cap_status)
{
	static int	was_here;
	int			str_cnt;
	t_light		light;
	double		brightness;

	if (was_here == 0)
		cap_status++;
	else
	{
		*status = ERROR;
		return ;
	}
	str_cnt = 0;
	while (splited_line[str_cnt])
		str_cnt++;
	if (str_cnt != 4)
	{
		*status = ERROR;
		return ;
	}
	light.origin = parse_three_double(&splited_line[1], status);
	brightness = atod(&splited_line[2], status);
	light.color = parse_three_double(&splited_line[3], status);
	add_light_hittable(&mlx->world, light);
	was_here = 1;
}
