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

t_color	get_surface_color(t_record *hit_record)
{
	if (hit_record->suface.checkerboard)
	{
		if (((int)hit_record->origin.e[0] + (int)hit_record->origin.e[1]
				+ (int)hit_record->origin.e[2]) % 2)
			return (init_color(66, 73, 87));
		else
			return (init_color(238, 238, 238));
	}
	else
		return (v_mul_scalar(&hit_record->suface.color,
				1 + hit_record->suface.brightness_rate));
}

// t_color	ray_color(t_ray ray, t_hittable *world, int depth)
// {
// 	t_record	hit_record;
// 	t_color		diffuse;
// 	t_color		specular;
// 	t_color		color;
// 	t_color		sum;

// 	if (depth < 0)
// 		return (init_color(0, 0, 0));
// 	else if (hit(ray, world, hit_record))
// 	{
// 		diffuse = ray_color(diffuse_ray(ray, hit_record), world, depth - 1);
// 		diffuse = v_add(&diffuse, &world->ambiance);
// 		color = get_color(&hit_record);
// 		sum = v_mul(&diffuse, &color);
// 		specular = ray_color(specular_ray(ray, hit_record), world, depth - 1);
// 		specular = v_add(&diffuse, &world->ambiance);
// 		return (v_add(&sum, &specular));
// 	}
// 	else
// 		return (v_add(&world->ambiance, &world->background));
// }

//spot brightness is needed
//light attenuation is also needed
//phong relfection is not implemented yet.
//brightness limit is needed to be implemented

double	clamp(double d, double min, double max)
{
	if (d < min)
		d = min;
	if (d > max)
		d = max;
	return (d);
}

double	attenuation(t_point3 start, t_point3 end)
{
	double	dist;
	double	coefficient;

	dist = v_length(v_sub(start, end));
	coefficient = 10;
	return (clamp(coefficient / dist, 0.0, 1.0));
}

t_color	light_from_spot(t_point3 point, t_hittable *world)
{
	t_color		ret;
	t_ray		incident;
	t_record	hit_record;
	int			index;

	ret = init_color(0, 0, 0);
	index = -1;
	while (++index < world->cur_light_count)
	{
		incident.origin = point;
		incident.dir = v_unit(v_sub(world->light[index].origin, point));
		if (hit(incident, world, &hit_record))
			if (v_length_squared(v_sub(hit_record.origin, point)) < v_length_squared(v_sub(world->light[index].origin, point)))
				continue ;
		
	}
	if (hit())
}

t_color	ray_color(t_ray ray, t_hittable *world, int depth)
{
	t_record	hit_record;
	t_color		diffuse;
	t_color		specular;
	t_color		common;

	if (depth < 0)
		return (init_color(0, 0, 0));
	else if (hit(ray, world, &hit_record))
	{
		diffuse = ray_color(diffuse_ray(ray, hit_record), world, depth);
		diffuse = v_mul_scalar(diffuse, hit_record.suface.diffuse_rate);
		specular = ray_color(specular_ray(ray, hit_record), world, depth);
		specular = v_mul_scalar(specular, hit_record.suface.specular_rate);
		common = v_add(world->ambiance, light_from_spot(&hit_record, world));
	}
	else
	{
	
	}
}
