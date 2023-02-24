#include "struct.h"
#include "macro.h"
#include "function.h"

void	free_two_dimension(char **to_free)
{
	int	i;

	i = 0;
	// printf("========= free =========\n");
	// for (int i = 0; to_free[i]; i++)
	// 	printf("%s\n", to_free[i]);
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
	char	**splited_line;

	if (line[0] == '\n')
		return (OK);
	status = OK;
	splited_line = ft_split(line, S_SPACES);
	if (ft_strcmp(splited_line[0], S_AMBIENT) == OK)
		parse_ambient(splited_line, mlx, &status, cap_status);
	else if (ft_strcmp(splited_line[0], S_CAMERA) == OK)
		parse_camera(splited_line, mlx, &status, cap_status);
	else if (ft_strcmp(splited_line[0], S_LIGHT) == OK)
		parse_light(splited_line, mlx, &status, cap_status);
	else if (ft_strcmp(splited_line[0], S_BACK) == OK)
		parse_background(splited_line, mlx, &status, cap_status);
	else if (ft_strcmp(splited_line[0], S_SPHERE) == OK)
		parse_sphere(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_PLANE) == OK)
		parse_plane(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_CYLINDER) == OK)
		parse_cylinder(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], S_CONE) == OK)
		parse_cone(splited_line, mlx, &status);
	else if (ft_strcmp(splited_line[0], "#") != OK)
		status = ERROR;
	free_two_dimension(splited_line);
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
	while (status[LINE] != ERROR)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (parse_object(line, mlx, &status[CAPITAL]) == ERROR)
		{
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
