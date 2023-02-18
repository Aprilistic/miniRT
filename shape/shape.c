#include "../includes/shape.h"

void init_sphere()
{
}

void	init_shape(t_shape *shape, int type, t_color *color, void *info)
{
	shape->type = type;
	shape->color = *color;
	if (type == SPHERE)
	{
		shape->hit = /* sphere_hit */;
		shape->characteristic = info;
	}
	else if (type == PLANE)
	{
		shape->hit = /* plane_hit */;
		shape->characteristic = info;
	}
	else if (type == CONE)
	{
		shape->hit = /* cone_hit */;
		shape->characteristic = info;
	}
	else if (type == CYLINDER)
	{
		shape->hit = /* cylinder_hit */;
		shape->characteristic = info;
	}
}
