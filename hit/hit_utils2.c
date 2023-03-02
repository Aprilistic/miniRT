#include "../function.h"
#include "../macro.h"
#include "../struct.h"

t_vec3	get_cylinder_normal(t_vec3 *intersect, t_cylinder *cylinder)
{
	t_vec3	bottom;
	t_vec3	center;
	double	root;
	double	coefft[2];

	bottom = v_add(cylinder->center, v_mul_scalar(cylinder->dir, -cylinder->height / 2));
	coefft[0] = v_dot(cylinder->dir, cylinder->dir);
	coefft[1] = 2.0 * v_dot(v_sub(bottom, *intersect), cylinder->dir);
	root = (-coefft[1]) / (2.0 * coefft[0]);
	center = v_add(bottom, v_mul_scalar(cylinder->dir, root));
	return (v_unit(v_sub(*intersect, center)));
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
