/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:37:12 by jinheo            #+#    #+#             */
/*   Updated: 2023/03/02 19:37:13 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "struct.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

/*	t_vec3 */
t_vec3	v_init(double e0, double e1, double e2);
t_vec3	v_unit(t_vec3 vector);
double	v_length(t_vec3 vector);
double	v_length_squared(t_vec3 vector);

t_vec3	v_add(t_vec3 left, t_vec3 right);
t_vec3	v_sub(t_vec3 left, t_vec3 right);
double	v_dot(t_vec3 left, t_vec3 right);
t_vec3	v_cross(t_vec3 left, t_vec3 right);
t_vec3	v_mul(t_vec3 left, t_vec3 right);
t_vec3	v_mul_scalar(t_vec3 vector, double scalar);

/* brightness.c */
void	limit_color_brightness(t_color *color);
double	attenuation(t_point3 start, t_point3 end);
t_color	light_from_spot(t_record *point, t_hittable *world);

/* color.c */
t_color	ray_color(t_ray ray, t_hittable *world, int depth);

/* reflection.c */
t_ray	diffuse_ray(t_record hit_record);
t_ray	specular_ray(t_ray incident, t_record hit_record);

/*  parsing functions  */
int		parse(char *file, t_mlx *mlx, int *errno);
int		parse_object(char *line, t_mlx *mlx, int *errno, int *cap_cnt);
void	free_two_dimension(char **to_free);
void	parse_ambient(char **splited_line, t_mlx *mlx, int *status,
			int *cap_status);
void	parse_camera(char **splited_line, t_mlx *mlx, int *status,
			int *cap_status);
void	parse_light(char **splited_line, t_mlx *mlx, int *status,
			int *cap_status);
void	parse_background(char **splited_line, t_mlx *mlx, int *status,
			int *cap_status);
void	parse_sphere(char **splited_line, t_mlx *mlx, int *status);
void	parse_plane(char **splited_line, t_mlx *mlx, int *status);
void	parse_cylinder(char **splited_line, t_mlx *mlx, int *status);
void	parse_cone(char **splited_line, t_mlx *mlx, int *status);
double	atod(char *str, int *status);
double	parse_atod(char **str, int *status);
double	integer_part(char **str, int *status);
double	decimal_part(char **str, int *status);
t_vec3	parse_three_double(char *str, int *status);
void	check_rgb(t_color *color, int *errno);
void	check_ratio(double ratio, int *errno);

/*  our_mlx functions  */
void	init_mlx(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_mlx *mlx);
int		destroy_window(t_mlx *mlx);
void	minirt_hook(t_mlx *mlx);
int		mouse_hook(int mouse_code, int x, int y, t_mlx *mlx);

/* hittable functions */
void	init_hittable(t_hittable *world);
void	resize_hittable(t_hittable *world, int is_object);
void	add_object_hittable(t_hittable *world, t_object object);
void	add_light_hittable(t_hittable *world, t_light light);
void	delete_hittable(t_hittable *world);

/* camera.c */
void	camera_location_move(t_mlx *mlx, int keycode);
int		camera_fov_change(t_mlx *mlx, int keycode);

/* render.c */
void	make_image(t_mlx *mlx);

/* hit function */
int		hit(t_ray ray, t_hittable *world, t_record *hit_record);
int		hit_by_plane(t_ray ray, t_object *object, t_record *hit_record);
int		closer_contact(t_ray ray, t_point3 contact, t_record *hit_record);
void	update_hit_record(t_point3 contact, t_vec3 normal, t_texture surface,
		t_record *hit_record);
void	set_face_normal(t_ray ray, t_record *hit_record);
int		hit_by_cylinder(t_ray ray, t_object *object, t_record *hit_record);
int		straight_curve_intersection(t_ray ray, double *coefft
			, t_point3 *contact);
t_vec3	get_cylinder_normal(t_ray ray, t_vec3 *intersect, t_cylinder *cylinder);

#endif
