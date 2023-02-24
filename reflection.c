#include "struct.h"
#include "function.h"

#include <time.h>
#include <stdlib.h>

double	random_double(double min, double max)
{
	double	range;
	double	div;

	srand(time(NULL));
	range = max - min;
	div = RAND_MAX / range;
	return (min + (rand() / div));
}

t_ray	diffuse_ray(t_record hit_record)
{
	t_ray	ret;
	t_vec3	random_unit_vec;

	ret.origin = hit_record.origin;
	random_unit_vec = v_init(random_double(-1, 1), random_double(-1, 1),
			random_double(-1, 1));
	random_unit_vec = v_unit(random_unit_vec);
	ret.dir = v_add(hit_record.normal, random_unit_vec);
	ret.dir = v_unit(ret.dir);
	return (ret);
}

t_ray	specular_ray(t_ray incident, t_record hit_record)
{
	t_ray	ret;
	t_vec3	tmp;
	double	h;

	ret.origin = hit_record.origin;
	h = v_dot(incident.dir, hit_record.normal);
	tmp = v_mul_scalar(hit_record.normal, h * 2);
	ret.dir = v_add(tmp, incident.dir);
	ret.dir = v_unit(ret.dir);
	return (ret);
}
