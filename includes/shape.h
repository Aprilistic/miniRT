#ifndef SHAPE_H
# define SHAPE_H
# include "ray.h"
# include "vec3.h"

enum e_type
{
	CONE,
	PLANE,
	SPHERE,
	CYLINDER,
};

typedef struct s_cone
{
	t_point3	point;
	double		height;
	double		diameter;
}	t_cone;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		dir_vector;
}	t_plane;

typedef struct s_sphere
{
	t_point3	center;
	double		diameter;
}	t_sphere;

typedef struct s_cylinder
{
	t_point3	point;
	t_vec3		dir_vector;
	double		diameter;
	double		height;
}	t_cylinder;

typedef struct s_shape
{
	int		type;
	int		option;
	t_color	color;
	void	*characteristic;
}	t_shape;

#endif
