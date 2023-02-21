#include "struct.h"

t_color	init_color(double r, double g, double b)
{
	t_color	ret;

	ret.e[0] = r;
	ret.e[1] = g;
	ret.e[2] = b;
	return (ret);
}

t_color	ray_color(t_ray *ray, t_hittable *world, int depth)
{
	t_record	hit_record;
	t_color		diffuse;
	t_color		specular;
	t_color		ambiance;

	if (depth < 0)
		return (init_color(0, 0, 0));
	else if (hit(ray, world, &hit_record))
	{
		return ((ray_color(diffusion(ray, &hit_record), world, depth - 1) * diffuse_rate
				+ ray_color(specular(ray, &hit_record), world, depth - 1) * specular_rate
				+ ambiance)
					* color);
	}
	else {
		return ((background + ambiance) * color);
	}
}
