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

t_color	ray_color(t_ray ray, t_hittable *world, int depth)
{
	t_record	hit_record;
	t_color		diffuse;
	t_color		specular;
	t_color		ambiance;

	if (depth < 0)
		return (init_color(0, 0, 0));
	else if (hit(ray, world, hit_record))
	{
		diffuse = ray_color(diffuse_ray(ray, hit_record), world, depth - 1);
		specular = ray_color(specular_ray(ray, hit_record), world, depth - 1);
	}
	else
	{
		return ((background + ambiance) * color);
	}
}

double	random_double(double min, double max)
{
	double	range;
	double	div;

	range = max - min;
	div = RAND_MAX / range;
	return (min + (rand() / div));
}

t_ray	diffuse_ray(t_ray incident, t_record hit_record)
{
	t_ray	ret;
	t_vec3	random_unit_vec;

	srand(time(NULL));
	ret.origin = hit_record.origin;
	random_unit_vec = v_init(random_double(-1, 1), random_double(-1, 1),
			random_double(-1, 1));
	random_unit_vec = v_unit(&random_unit_vec);
	ret.dir = v_add(&hit_record.normal, &random_unit_vec);
	ret.dir = v_unit(&ret.dir);
	return (ret);
}

t_ray	specular_ray(t_ray incident, t_record hit_record)
{
	t_ray	ret;
	t_vec3	tmp;
	double	h;

	ret.origin = hit_record.origin;
	h = v_dot(&incident.dir, &hit_record.normal);
	tmp = v_mul_scalar(&hit_record.normal, h * 2);
	ret.dir = v_add(&tmp, &incident.dir);
	ret.dir = v_unit(&ret.dir);
	return (ret);
}
