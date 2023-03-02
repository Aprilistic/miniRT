#include "../function.h"
#include "../macro.h"
#include "../struct.h"

t_vec3	get_cylinder_normal(t_vec3 *intersect, t_cylinder *cylinder)
{
	t_vec3	center;
	t_vec3	normal;
	double	length;

	length = v_dot(cylinder->dir, v_sub(*intersect, cylinder->center));
	center = v_mul_scalar(cylinder->dir, length);
	normal = v_unit(v_sub(*intersect, center));
	return (normal);
}

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
