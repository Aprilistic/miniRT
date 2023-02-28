#include "../function.h"
#include "../macro.h"
#include "../struct.h"

int	hit_by_real_cylinder(t_ray ray, t_cylinder *cylinder, t_record *hit_record)
{
	t_vec3			save;
	double			coefft[3];

	// 원기둥과 만나는지 구하기
	save = v_sub(ray.origin, cylinder->center);
	coefft[0] = v_length_squared(v_cross(cylinder->dir, ray.dir));
	coefft[1] = 2.0 * v_dot(v_cross(cylinder->dir, save), v_cross(cylinder->dir, ray.dir));
	coefft[2] = v_length_squared(v_cross(cylinder->dir, save)) - pow(cylinder->diameter / 2, 2);
	if (!straight_curve_intersection(ray, coefft, &contact)
		&& )
	{
		hit = 1;
		if (closer_contact(ray, contact, hit_record))
			update_hit_record(contact, );
	}
}

int	hit_by_cylinder(t_ray ray, t_object *object, t_record *hit_record)
{
	t_cylinder		*cylinder;
	t_point3		contact;
	int				hit;

	hit = 0;
	cylinder = (t_cylinder *)(object)->equation;
	// 덮개와 만나는지 구하기
	return (hit);
}
