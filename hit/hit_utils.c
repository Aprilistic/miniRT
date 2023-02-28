#include "../function.h"
#include "../macro.h"
#include "../struct.h"

int	closer_contact(t_ray ray, t_point3 contact, t_record *hit_record)
{
	double	new_dist;
	double	old_dist;

	new_dist = v_length(v_sub(ray.origin, contact));
	if (new_dist <= EPSILON || MAX_DIST <= new_dist)
		return (0);
	old_dist = v_length(v_sub(ray.origin, hit_record->origin));
	if (new_dist < old_dist)
		return (1);
	return (0);
}

void	update_hit_record(t_point3 contact, t_vec3 normal, t_texture surface,
		t_record *hit_record)
{
	hit_record->origin = contact;
	hit_record->normal = normal;
	hit_record->suface = surface;
}

void	set_face_normal(t_ray ray, t_record *hit_record)
{
	if (v_dot(ray.dir, hit_record->normal) > 0)
		hit_record->normal = v_mul_scalar(hit_record->normal, -1);
}

int	hit_by_circles(t_ray ray, t_object *object, t_record *hit_record)
{
	double		dot_product;
	double		root;
	t_plane		*plane;
	t_point3	contact;

	dot_product = v_dot(plane->normal, ray.dir);
	if (fabs(dot_product) < EPSILON)
		return (0);
	root = v_dot(v_sub(plane->point, ray.origin), plane->normal) / dot_product;
	if (root < 0)
		return (0);
	contact = v_add(ray.origin, v_mul_scalar(ray.dir, root));
	if (closer_contact(ray, contact, hit_record))
	{
		update_hit_record(contact, plane->normal, object->surface, hit_record);
		set_face_normal(ray, hit_record);
		return (1);
	}
	return (0);
}

int	hit_by_cylinder(t_ray ray, t_object *object, t_record *hit_record)
{
	t_cylinder		*cylinder;
	t_point3		contact;
	t_vec3			save;
	double			coefft[3];
	int				hit;

	hit = 0;
	cylinder = (t_cylinder *)(object)->equation;
	// 원기둥과 만나는지 구하기
	save = v_sub(ray.origin, cylinder->center);
	coefft[0] = v_length_squared(v_cross(cylinder->dir, ray.dir));
	coefft[1] = 2.0 * v_dot(v_cross(cylinder->dir, save), v_cross(cylinder->dir, ray.dir));
	coefft[2] = v_length_squared(v_cross(cylinder->dir, save)) - pow(cylinder->diameter / 2, 2);
	if (!straight_curve_intersection(ray, coefft, &contact))
	{

	}
	// 덮개와 만나는지 구하기
	if (closer_contact(ray, contact, hit_record))
	{
		return (1);
	}
	return (0);
}
