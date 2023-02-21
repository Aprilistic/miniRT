#include "struct.h"
#include "function.h"

void	init_hittable(t_hittable *world)
{
	world->max_object_count = 8;
	world->cur_object_count = 0;
	world->object = ft_calloc(world->max_object_count, sizeof(t_object));
	world->max_light_count = 8;
	world->cur_light_count = 0;
	world->light = ft_calloc(world->max_light_count, sizeof(t_object));
}

void	resize_hittable(t_hittable *world, int is_object)
{
	t_object	**resized;

	if (is_object)
	{
		world->max_object_count *= 2;
		resized = ft_calloc(world->max_object_count, sizeof(t_object));
		ft_memcpy(resized, world->object, world->max_object_count / 2 * sizeof(t_object));
		free(world->object);
		world->object = resized;
	}
	else
	{
		world->max_light_count *= 2;
		resized = ft_calloc(world->max_light_count, sizeof(t_object));
		ft_memcpy(resized, world->light, world->max_light_count / 2 * sizeof(t_object));
		free(world->light);
		world->light = resized;
	}
}

void	add_object_hittable(t_hittable *world, t_object object)
{
	if (world->max_object_count == world->cur_object_count)
		resize_hittable(world, 1);
	world->object[world->cur_object_count] = object;
	world->cur_object_count++;
}

void	add_light_hittable(t_hittable *world, t_light light)
{
	if (world->max_light_count == world->cur_light_count)
		resize_hittable(world, 0);
	world->light[world->cur_light_count] = light;
	world->cur_light_count++;
}

void	delete_hittable(t_hittable *world)
{
	int	free_idx;

	free_idx = 0;
	while (free_idx < world->cur_object_count)
	{
		free(world->object[free_idx].equation);
		free_idx++;
	}
	free(world->object);
	free(world->light);
}
