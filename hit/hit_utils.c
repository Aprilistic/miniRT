#include "../function.h"
#include "../macro.h"
#include "../struct.h"

int	in_the_height(t_point3 *contact, t_cylinder *cylinder, double height)
{
	double	contact_height;

	contact_height = v_dot(v_sub(*contact, cylinder->center), cylinder->dir);
	return (-height / 2 <= contact_height && contact_height <= height / 2);
}

int	hit_by_real_cylinder(t_ray *ray, t_cylinder *cylinder,
	t_texture *surface, t_record *hit_record)
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
		&& in_the_height(&contact, cylinder, cylinder->height))
	{
		if (closer_contact(*ray, contact, hit_record))
			update_hit_record(contact,
				get_cylinder_normal(&hit_record->origin, cylinder),
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
	return (hit_by_real_cylinder(&ray, cylinder, &object->surface, hit_record));
}
