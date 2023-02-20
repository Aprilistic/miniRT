#include "../includes/shape.h"

double	hit_sphere(const t_sphere *)

	void init_shape(t_shape *shape, int type, t_texture *color, void *info)
{
	shape->type = type;
	shape->color = *color;
	shape->characteristic = info;
	if (type == SPHERE)
		shape->hit = /* sphere_hit */;
	else if (type == PLANE)
		shape->hit = /* plane_hit */;
	else if (type == CONE)
		shape->hit = /* cone_hit */;
	else if (type == CYLINDER)
		shape->hit = /* cylinder_hit */;
}
