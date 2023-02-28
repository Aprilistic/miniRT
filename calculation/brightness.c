#include "../function.h"
#include "../macro.h"
#include "../struct.h"
#include <math.h>
#include <stdlib.h>

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

t_color	light_from_spot(t_record *point, t_hittable *world)
{
	t_color		ret;
	t_ray		incident;
	t_color		incident_color;
	t_record	hit_record;
	int			index;

	ret = v_init(0, 0, 0);
	index = -1;
	while (++index < world->cur_light_count)
	{
		hit_record.origin = v_init(INF, INF, INF);
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
