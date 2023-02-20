#ifndef PARSE_H
# define PARSE_H
# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLAIN "pl"
# define CYLINDER "cy"
# define CONE "co"
# define SPACES " \t\r\n\v\f"
# define OK 0
# define ERROR -1

int		parse(char *file, t_mlx *mlx);
int		add_object(char *line, t_mlx *mlx);
void	free_two_dimension(char **to_free);
void	parse_ambient(char **splited_line, t_mlx *mlx, int *status);
void	parse_camera(char **splited_line, t_mlx *mlx, int *status);
void	parse_light(char **splited_line, t_mlx *mlx, int *status);
void	parse_sphere(char **splited_line, t_mlx *mlx, int *status);
void	parse_plain(char **splited_line, t_mlx *mlx, int *status);
void	parse_cylinder(char **splited_line, t_mlx *mlx, int *status);
void	parse_cone(char **splited_line, t_mlx *mlx, int *status);

#endif