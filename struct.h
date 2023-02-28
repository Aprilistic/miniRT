#ifndef STRUCT_H
# define STRUCT_H

# include "macro.h"

typedef struct s_vec3
{
	double		e[3];
}				t_vec3;
typedef t_vec3	t_color;
typedef t_vec3	t_point3;

typedef struct s_ray
{
	t_vec3		dir;
	t_point3	origin;
}				t_ray;

typedef struct s_camera
{
	t_vec3		dir;
	t_vec3		u;
	t_vec3		v;
	t_point3	origin;
	int			fov;
}				t_camera;

typedef struct s_texture
{
	t_color		color;
	double		diffuse_rate;
	double		specular_rate;
	double		brightness_rate;
}				t_texture;

typedef struct s_object
{
	int			type;
	t_texture	surface;
	void		*equation;
}				t_object;

typedef struct s_light
{
	t_point3	origin;
	t_color		color;
}				t_light;

typedef struct s_hittable
{
	int			max_object_count;
	int			cur_object_count;
	t_object	*object;
	int			max_light_count;
	int			cur_light_count;
	t_light		*light;
	t_color		ambiance;
	t_color		background;
}				t_hittable;

typedef struct s_record
{
	t_point3	origin;
	t_vec3		normal;
	t_texture	suface;
}				t_record;

/*  shape structures  */

typedef struct s_cone
{
	t_point3	center;
	t_point3 coefficient; // 계수
}				t_cone;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
}				t_plane;

typedef struct s_sphere
{
	t_point3	center;
	double		diameter;
}				t_sphere;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		dir_vector;
	double		diameter;
	double		height;
}				t_cylinder;

/* image structure */
typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

/* mlx structure */
typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		img;
	t_hittable world; // object, ambiance, light
	t_camera camera;  // camera
}				t_mlx;

#endif
