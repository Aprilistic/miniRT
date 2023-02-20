#include "shape.h"
#include "ray.h"

#include <math.h>
#include <stdbool.h>

t_shape *find_closest_object(t_hittable *world, t_ray *ray)
{
	int	index;
	t_vec3	hitting_point;
	double	dist;
	double	min_dist;
	int		min_index;

	index = 0;
	min_dist = INFINITY;
	min_index = -1;
	while (index < world->cur_count)
	{
		hitting_point = get_hitting_point(world->objects[index], ray);
		dist = get_3rd_distance(ray->origin, hitting_point);
		if (dist<min_dist)
		{
			min_dist = dist;
			min_index = index;
		}
		index++;
	}
	if (index < 0)
		return (NULL);
	return (world->object[index]);
}

bool	hit(t_hittable *world, t_ray *ray)
{
	t_shape	*closest_object;

	closest_object = find_closest_object(world, ray);
	if (closest_object)
	{
		update_ray(t_shape *object, t_ray *ray);
		return (true);
	}
	return (false);
}

t_color	ray_color(const t_ray *r, const t_hittables *world, int depth)
{
	t_color	ret;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	if (depth <= 0)
		return (ret);
	if (world.hit())
	{
		//world hit 에서 새로운 ray 반환
		return (cos(radian)*ray_color(r, world, depth - 1));
	}
	return (constant * color + (1 - constant) * background_color);

}
