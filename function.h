#ifndef FUNCTION_H
# define FUNCTION_H
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "struct.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

/*	t_vec3 */
/* initialize */
t_vec3	v_init(double e0, double e1, double e2);

/* unit vector */
t_vec3	v_unit(t_vec3 vector);

/* length */
double	v_length(t_vec3 vector);
double	v_length_squared(t_vec3 vector);

/* addition, subtraction, dot, cross, mul vector, mul scalar */
t_vec3	v_add(t_vec3 left, t_vec3 right);
t_vec3	v_sub(t_vec3 left, t_vec3 right);
double	v_dot(t_vec3 left, t_vec3 right);
t_vec3	v_cross(t_vec3 left, t_vec3 right);
t_vec3	v_mul(t_vec3 left, t_vec3 right);
t_vec3	v_mul_scalar(t_vec3 vector, double scalar);

t_color	init_color(double r, double g, double b);
t_color	ray_color(t_ray ray, t_hittable *world, int depth);
double	random_double(double min, double max);
t_ray	diffuse_ray(t_ray incident, t_record hit_record);
t_ray	specular_ray(t_ray incident, t_record hit_record);

/*  parsing functions  */
int		parse(char *file, t_mlx *mlx);
int		parse_object(char *line, t_mlx *mlx, int *cap_status);
void	free_two_dimension(char **to_free);
void	parse_ambient(char **splited_line, t_mlx *mlx
						, int *status, int *cap_status);
void	parse_camera(char **splited_line, t_mlx *mlx
						, int *status, int *cap_status);
void	parse_light(char **splited_line, t_mlx *mlx
						, int *status, int *cap_status);
void	parse_sphere(char **splited_line, t_mlx *mlx, int *status);
void	parse_plane(char **splited_line, t_mlx *mlx, int *status);
void	parse_cylinder(char **splited_line, t_mlx *mlx, int *status);
void	parse_cone(char **splited_line, t_mlx *mlx, int *status);
double	atod(char *str, int *status);
double	parse_atod(char **str, int *status);
double	integer_part(char **str, int *status);
double	decimal_part(char **str, int *status);
t_vec3	parse_three_double(char *str, int *status);
int		check_rgb(t_color *color);

/*  our_mlx functions  */
void	init_mlx(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_mlx *mlx);
int		destroy_window(t_mlx *mlx);
void	minirt_hook(t_mlx *mlx);

/* hittable functions */
void	init_hittable(t_hittable *world);
void	resize_hittable(t_hittable *world, int is_object);
void	add_object_hittable(t_hittable *world, t_object object);
void	add_light_hittable(t_hittable *world, t_light light);
void	delete_hittable(t_hittable *world);

/*	reflection functions	*/
t_ray	diffuse_ray(t_ray incident, t_record hit_record);
t_ray	specular_ray(t_ray incident, t_record hit_record);

/*	camera default value setting	*/
void	make_image(t_mlx *mlx);

#endif
