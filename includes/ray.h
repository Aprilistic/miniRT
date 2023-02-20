#ifndef RAY_H
# define RAY_H
# include "vec3.h"

typedef t_vec3	t_point3;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
	t_color		color;
}	t_ray;

#endif
