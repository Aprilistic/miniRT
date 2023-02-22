#include "struct.h"

int	hit(t_ray ray, t_hittable *world, t_record *hit_record)
{
	int	index;
	int	hit_surface;

	hit_surface = 0;
	index = 0;
	while (index < world->cur_object_count)
	{
		if (hit_by_object())
		{
			update_hit_record();
			hit_surface = 1;
		}
		index++;
	}
	return (hit_surface);
}
