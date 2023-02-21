#include "struct.h"
#include "function.h"

void	init_hittable(t_hittable *world)
{
	world->max_count = 8;
	world->cur_count = 0;
	world->object = ft_calloc(world->max_count, sizeof(t_shape *));
}

void	resize_hittable(t_hittable *world)
{
	t_shape	**resized;

	world->max_count *= 2;
	resized = ft_calloc(world->max_count, sizeof(t_shape *));
	ft_memcpy(resized, world->object, world->max_count / 2 * sizeof(t_shape *));
	free(world->object);
	world->object = resized;
}

void	add_to_hittable(t_hittable *world, t_shape *object)
{
	if (world->max_count == world->cur_count)
		resize_hittable(world);
	world->object[world->cur_count] = object;
	world->cur_count++;
}

void	delete_hittable(t_hittable *world)
{
	int	free_idx;

	free_idx = 0;
	while (free_idx < world->cur_count)
	{
		free(world->object[free_idx].characteristic);
		free_idx++;
	}
	free(world->object);
}
