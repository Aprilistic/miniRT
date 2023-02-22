#include "struct.h"
#include "macro.h"

// 각 타입에 따라서 만나는 지점을 구하는 함수로 들어간다.
int	hit_by_object(t_ray ray, t_object *object, t_record *hit_record)
{
	if (object->type == SPHERE)
	{
		// 구에
	}
}

void	update_hit_record(t_record *main, t_record *cmp)
{
	// main보다 cmp가 가깝다면
		*main = *cmp;
}

int	hit(t_ray ray, t_hittable *world, t_record *hit_record)
{
	int			index;
	int			hit_surface;
	t_record	cmp;

	hit_surface = 0;
	index = 0;
	while (index < world->cur_object_count)
	{
		if (hit_by_object(ray, &world->object[index], &cmp))
		{
			update_hit_record(&hit_record, &cmp);
			hit_surface = 1;
		}
		index++;
	}
	return (hit_surface);
}