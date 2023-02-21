#ifndef STRUCT_H
# define STRUCT_H

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
typedef t_ray	t_camera;

typedef struct s_texture
{
	int			checkerboard;
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
	t_object	**object;
	int			max_light_count;
	int			cur_light_count;
	t_light		**light;
}				t_hittable;

typedef struct s_record
{
	t_point3	origin;
	t_vec3		normal;
	t_texture	suface;
}				t_record;

typedef struct s_setting
{
	double		ambiance;
	t_color		background;
	/* resolution.... etc*/
}				t_setting;

/*  shape structures  */

typedef struct s_cone
{
	t_point3	point;
	double		height;
	double		diameter;
}				t_cone;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		dir_vector;
}				t_plane;

typedef struct s_sphere
{
	t_point3	center;
	double		diameter;
}				t_sphere;

typedef struct s_cylinder
{
	t_point3	point;
	t_vec3		dir_vector;
	double		diameter;
	double		height;
}				t_cylinder;

typedef struct s_shape
{
	int			type;
	int			option;
	t_texture	color;
	void		*characteristic;
}				t_shape;

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
	t_hittable	*obj_list;
}				t_mlx;

#endif
