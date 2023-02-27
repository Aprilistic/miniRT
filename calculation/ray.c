#include "../function.h"
#include "../macro.h"
#include "../struct.h"
#include <math.h>
#include <stdlib.h>

t_color	get_surface_color(t_record *hit_record)
{
	if (hit_record->suface.checkerboard)
	{
		if (((int)hit_record->origin.e[0] + (int)hit_record->origin.e[1]
				+ (int)hit_record->origin.e[2]) % 2)
			return (v_init(66, 73, 87));
		else
			return (v_init(238, 238, 238));
	}
	else
		return (hit_record->suface.color);
}

double	clamp(double d, double min, double max)
{
	if (d < min)
		d = min;
	else if (d > max)
		d = max;
	return (d);
}

void	limit_color_brightness(t_color *color)
{
	color->e[0] = clamp(color->e[0], 0, 255);
	color->e[1] = clamp(color->e[1], 0, 255);
	color->e[2] = clamp(color->e[2], 0, 255);
}

double	attenuation(t_point3 start, t_point3 end)
{
	double	dist;

	dist = v_length(v_sub(start, end));
	return (clamp(LIGHT_ATTENUATION / dist, 0.0, 1.0));
}

void	set_face_normal(t_ray ray, t_record *hit_record)
{
	if (v_dot(ray.dir, hit_record->normal) > 0)
		hit_record->normal = v_mul_scalar(hit_record->normal, -1);
}

t_color	light_from_spot(t_record *point, t_hittable *world)
{
	t_color		ret;
	t_ray		incident;
	t_color		incident_color;
	t_record	hit_record;
	int			index;

	ret = v_init(0, 0, 0);
	hit_record.origin = v_init(INF, INF, INF);
	index = -1;
	while (++index < world->cur_light_count)
	{
		incident.origin = point->origin;
		incident.dir = v_unit(v_sub(world->light[index].origin, point->origin));
		if (hit(incident, world, &hit_record))
			if (v_length_squared(v_sub(hit_record.origin, point->origin))
				< v_length_squared(v_sub(world->light[index].origin,
						point->origin)))
				continue ;
		incident_color = v_mul_scalar(world->light[index].color,
				v_dot(point->normal, incident.dir)
				* attenuation(point->origin, world->light[index].origin));
		ret = v_add(ret, incident_color);
	}
	return (ret);
}

t_color	ray_color(t_ray ray, t_hittable *world, int depth)
{
	t_record	hit_record;
	t_color		diffuse;
	t_color		specular;
	t_color		common;
	t_color		sum;

	hit_record.origin = v_init(INF, INF, INF);
	if (depth < 0)
		return (v_init(0, 0, 0));
	else if (hit(ray, world, &hit_record))
	{
		common = v_add(world->ambiance, light_from_spot(&hit_record, world));
		common = v_add(common, v_mul_scalar(get_surface_color(&hit_record), hit_record.suface.brightness_rate));
		limit_color_brightness(&common);
		diffuse = ray_color(diffuse_ray(hit_record), world, depth - 1);
		diffuse = v_add(diffuse, common);
		diffuse = v_mul(diffuse, get_surface_color(&hit_record));
		diffuse = v_mul_scalar(diffuse, 1.0 / 255);
		diffuse = v_mul_scalar(diffuse, hit_record.suface.diffuse_rate);
		limit_color_brightness(&diffuse);
		specular = ray_color(specular_ray(ray, hit_record), world, depth - 1);
		specular = v_add(specular, common);
		specular = v_mul_scalar(specular, hit_record.suface.specular_rate);
		limit_color_brightness(&specular);
		sum = v_add(diffuse, specular);
		limit_color_brightness(&sum);
		return (v_mul_scalar(sum, attenuation(ray.origin, hit_record.origin)));
	}
	return (world->background);
}
