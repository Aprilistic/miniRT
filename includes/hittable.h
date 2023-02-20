#ifndef HITTABLE_H
# define HITTABLE_H

#include "ray.h"
#include "shape.h"

typedef struct s_hittable t_hittable;

struct s_hittable
{
	int			max_count;
	int			cur_count;
	t_shape		*object;
};

void		init_hittable(t_hittable *world);
void		resize_hittable(t_hittable *world);
void		add_to_hittable(t_hittable *world, t_shape *object);
void		delete_hittalbe(t_hittable *world);
t_hittable	*find_closest_object(t_hittable *world, t_ray *ray);
void		update_ray(t_shape *object, t_ray *ray);

#endif
