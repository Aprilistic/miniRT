#include "shape.h"
#include "ray.h"

#include <math.h>
#include <stdbool.h>

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
