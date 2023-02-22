#include "struct.h"
#include "macro.h"
#include "function.h"
#include <stdlib.h>
#include <fcntl.h>

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

int	parse_object(char *line, t_mlx *mlx, int *cap_status)
{
	int		status;
	char	**save;
	char	**splited_line;

	if (line[0] == '\n')
		return (OK);
	status = OK;
	splited_line = ft_split(line, S_SPACES);
	save = splited_line;
	if (ft_strcmp(splited_line[0], S_AMBIENT) == OK)
		parse_ambient(splited_line, mlx, &status, cap_status);
	else if (ft_strcmp(splited_line[0], S_CAMERA) == OK)
		parse_camera(splited_line, mlx, &status, cap_status);
	else if (ft_strcmp(splited_line[0], S_LIGHT) == OK)
		parse_light(splited_line, mlx, &status, cap_status);
	else if (ft_strcmp(splited_line[0], S_SPHERE) == OK)
		parse_sphere(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_PLANE) == OK)
		parse_plane(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_CYLINDER) == OK)
		parse_cylinder(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_CONE) == OK)
		parse_cone(splited_line, mlx, &status);
	free_two_dimension(save);
	return (status);
}

int	parse(char *file, t_mlx *mlx)
{
	int		fd;
	int		status[2];
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	status[LINE] = OK;
	status[CAPITAL] = OK;
	init_hittable(&mlx->world);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || parse_object(line, mlx, &status[CAPITAL]) == ERROR)
		{
			free(line);
			delete_hittable(&mlx->world);
			status[LINE] = ERROR;
		}
		free(line);
	}
	close(fd);
	if (status[CAPITAL] != CAP_CNT)
		status[LINE] = ERROR;
	return (status[LINE]);
}
