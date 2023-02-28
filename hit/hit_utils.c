#include "../function.h"
#include "../macro.h"
#include "../struct.h"

int	in_the_height(t_vec3 *contact, t_vec3 *dir, double height)
{
	double	contact_height;

	contact_height = v_dot(*contact, v_unit(*dir));
	return (-height / 2 <= contact_height && contact_height <= height / 2);
}

int	hit_by_one_circle(t_ray *ray, t_object *object, t_record *hit_record, double radius)
{
	t_record	backup;
	t_plane		*plane;

	backup = *hit_record;
	plane = (t_plane *)object->equation;
	if (hit_by_plane(*ray, object, hit_record))
	{
		if (v_length_squared(v_sub(plane->point, hit_record->origin))
			> pow(radius, 2))
			*hit_record = backup;
		return (1);
	}
	return (0);
}

int	hit_by_two_circles(t_ray *ray, t_cylinder *cylinder, t_texture *surface, t_record *hit_record)
{
	t_plane		plane;
	t_object	object;
	int			hit;

	hit = 0;
	object.type = PLANE;
	object.surface = *surface;
	object.equation = &plane;

	// 위 덮개
	plane.normal = v_init(0, -1, 0);
	// 여기서 그냥 y값을 더하면 안 된다. 기울어져 있을 때는 작동을 안 한다.
	plane.point = v_add(cylinder->center, v_init(0, cylinder->height / 2, 0));
	hit |= hit_by_one_circle(ray, &object, hit_record, cylinder->diameter / 2);

	// 아래 덮개
	plane.normal = v_init(0, 1, 0);
	plane.point = v_add(cylinder->center, v_init(0, -cylinder->height / 2, 0));
	hit |= hit_by_one_circle(ray, &object, hit_record, cylinder->diameter / 2);

	return (hit);
}

int	hit_by_real_cylinder(t_ray *ray, t_cylinder *cylinder, t_texture *surface, t_record *hit_record)
{
	t_vec3			save;
	t_vec3			contact;
	double			coefft[3];

	// 원기둥과 만나는지 구하기
	save = v_sub(ray->origin, cylinder->center);
	coefft[0] = v_length_squared(v_cross(cylinder->dir, ray->dir));
	coefft[1] = 2.0 * v_dot(v_cross(cylinder->dir, save), v_cross(cylinder->dir, ray->dir));
	coefft[2] = v_length_squared(v_cross(cylinder->dir, save)) - pow(cylinder->diameter / 2, 2);
	if (straight_curve_intersection(*ray, coefft, &contact)
		&& in_the_height(&contact, &ray->dir, cylinder->height))
	{
		if (closer_contact(*ray, contact, hit_record))
			update_hit_record(contact,
				get_cylinder_noraml(&hit_record->origin, cylinder),
					*surface, hit_record);
		return (1);
	}
	return (0);
}

int	hit_by_cylinder(t_ray ray, t_object *object, t_record *hit_record)
{
	t_cylinder		*cylinder;

	cylinder = (t_cylinder *)(object)->equation;
	// 위, 아래 만나는지 구하기
	return (hit_by_real_cylinder(&ray, cylinder, &object->surface, hit_record)
		|| hit_by_two_circles(&ray, cylinder, &object->surface, hit_record));
}
