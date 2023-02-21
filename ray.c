#include "function.h"
#include "includes/vec3.h"
#include "struct.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

t_color	init_color(double r, double g, double b)
{
	t_color	ret;

	ret.e[0] = r;
	ret.e[1] = g;
	ret.e[2] = b;
	return (ret);
}

t_color	get_color(t_record *hit_record)
{
	if (hit_record->suface.checkerboard)
	{
		if (((int)hit_record->origin.e[0] + (int)hit_record->origin.e[1]
				+ (int)hit_record->origin.e[2]) % 2)
			return (init_color(0, 0, 0));
		else
			return (init_color(255.99, 255.99, 255.99));
	}
	else
		return (hit_record->suface.color);
}

t_color	ray_color(t_ray ray, t_hittable *world, int depth)
{
	t_record	hit_record;
	t_color		diffuse;
	t_color		specular;
	t_color		surface;
	t_color		sum;

	if (depth < 0)
		return (init_color(0, 0, 0));
	else if (hit(ray, world, hit_record))
	{
		diffuse = ray_color(diffuse_ray(ray, hit_record), world, depth - 1);
		specular = ray_color(specular_ray(ray, hit_record), world, depth - 1);
		sum = v_add(&diffuse, &specular);
		sum = v_add(&sum, &ambiance);
		surface = get_color(&hit_record);
		return (v_mul(&sum, &surface));
	}
	else
	{
		return ((background + ambiance) * color);
	}
}
