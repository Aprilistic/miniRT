#include "../struct.h"
#include "../macro.h"
#include "../function.h"
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

int	add_object(char *line, t_mlx *mlx)
{
	int		status;
	char	**splited_line;

	if (line[0] == '\n')
		return (OK);
	splited_line = ft_split(line, S_SPACES);
	if (splited_line == NULL)
		return (ERROR);
	status = OK;
	if (ft_strcmp(splited_line[0], S_AMBIENT) == OK)
		parse_ambient(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_CAMERA) == OK)
		parse_camera(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_LIGHT) == OK)
		parse_light(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_SPHERE) == OK)
		parse_sphere(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_PLANE) == OK)
		parse_plane(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_CYLINDER) == OK)
		parse_cylinder(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_CONE) == OK)
		parse_cone(splited_line, mlx, &status);
	free_two_dimension(splited_line);
	return (status);
}

int	parse(char *file, t_mlx *mlx)
{
	int		fd;
	int		status;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	status = OK;
	init_hittable(mlx->obj_list);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || add_object(line, mlx) == ERROR)
		{
			free(line);
			delete_hittable(mlx->obj_list);
			status = ERROR;
		}
		free(line);
	}
	close(fd);
	return (status);
}
