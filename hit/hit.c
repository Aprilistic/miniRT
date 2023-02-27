#include "../function.h"
#include "../macro.h"
#include "../struct.h"

int	ray_sphere_contact(t_ray ray, double *coefft, t_point3 *contact)
{
	double		discriminant;
	double		root[2];
	t_point3	two_contact[2];

	discriminant = coefft[1] * coefft[1] - 4 * coefft[0] * coefft[2];
	if (discriminant <= 0)
		return (0);
	root[0] = (-coefft[1] - sqrt(discriminant)) / (2.0 * coefft[0]);
	root[1] = (-coefft[1] + sqrt(discriminant)) / (2.0 * coefft[0]);
	two_contact[0] = v_add(ray.origin, v_mul_scalar(ray.dir, root[0]));
	two_contact[1] = v_add(ray.origin, v_mul_scalar(ray.dir, root[1]));
	if (root[1] < 0)
		return (0);
	if (root[0] < 0)
		*contact = two_contact[1];
	else
		*contact = two_contact[0];
	return (1);
}

int	hit_by_sphere(t_ray ray, t_object *object, t_record *hit_record)
{
	t_sphere	*sphere;
	double		coefft[3];
	t_vec3		save;
	t_point3	contact;

	sphere = (t_sphere *)(object)->equation;
	coefft[0] = v_dot(ray.dir, ray.dir);
	save = v_sub(ray.origin, sphere->center);
	coefft[1] = 2 * v_dot(ray.dir, save);
	coefft[2] = v_dot(save, save) - pow(sphere->diameter / 2, 2);
	if (!ray_sphere_contact(ray, coefft, &contact))
		return (0);
	if (closer_contact(ray, contact, hit_record))
	{
		update_hit_record(contact, v_unit(v_sub(contact, sphere->center)),
			object->surface, hit_record);
		return (1);
	}
	return (0);
}

int	hit_by_plane(t_ray ray, t_object *object, t_record *hit_record)
{
	double		dot_product;
	double		root;
	t_plane		*plane;
	t_point3	contact;

	plane = (t_plane *)(object)->equation;
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

// 각 타입에 따라서 만나는 지점을 구하는 함수로 들어간다.
int	hit_by_object(t_ray ray, t_object *object, t_record *hit_record)
{
	if (object->type == SPHERE)
	{
		// 구와 만나는지 구하는 함수
		return (hit_by_sphere(ray, object, hit_record));
	}
	else if (object->type == CYLINDER)
	{
		// 원기둥과 만나는지 구하는 함수
		return (hit_by_cylinder(ray, object, hit_record));
	}
	else if (object->type == CONE)
	{
		// 콘과 만나는지 구하는 함수
	}
	else if (object->type == PLANE)
	{
		// 면과 만나는지 구하는 함수
		return (hit_by_plane(ray, object, hit_record));
	}
	return (0);
}

int	hit(t_ray ray, t_hittable *world, t_record *hit_record)
{
	int	index;
	int	hit_surface;

	hit_surface = 0;
	index = 0;
	while (index < world->cur_object_count)
	{
		if (hit_by_object(ray, &world->object[index], hit_record))
			hit_surface = 1;
		index++;
	}
	return (hit_surface);
}
