#include "../struct.h"
#include "../macro.h"
#include "../function.h"

void	set_closer_point(double root[2], t_ray *ray, t_record *hit_record)
{
	t_vec3	cmp;

	cmp = v_add(ray->origin, v_mul_scalar(ray->dir, root[0]));
	hit_record->origin = v_add(ray->origin, v_mul_scalar(ray->dir, root[1]));
	if (v_length_squared(v_sub(cmp, ray->origin))
		< v_length_squared(v_sub(hit_record->origin, ray->origin)))
		hit_record->origin = cmp;
}

int	hit_by_sphere(t_ray ray, t_object *object, t_record *hit_record)
{
	// P(t) = A + bt
	//        A : 광선, b : 광선의 방향
	// 이차 방정식 𝑡^2𝐛⋅𝐛+2𝑡𝐛⋅(𝐀−𝐂)+(𝐀−𝐂)⋅(𝐀−𝐂)−𝑟^2=0
	//          at^2 + bt + c = 0
	//          a = 𝐛⋅𝐛;
	//          b = 2 * 𝐛⋅(𝐀−𝐂)
	//          c = (𝐀−𝐂)⋅(𝐀−𝐂)−𝑟^2
	// 
	// printf("ray.origin : %lf, %lf, %lf\n", ray.origin.e[0], ray.origin.e[1], ray.origin.e[2]);
	double		root[2];
	double		coefft[3];
	double		discriminant;
	t_sphere	*sphere;
	t_vec3		save;

	sphere = (t_sphere *)(object)->equation;
	coefft[0] = v_dot(ray.dir, ray.dir);
	save = v_sub(ray.origin, sphere->center); //(A-C)
	coefft[1] = 2 * v_dot(ray.dir, save);
	coefft[2] = v_dot(save, save) - pow(sphere->diameter / 2, 2);
	discriminant = coefft[1] * coefft[1] - 4 * coefft[0] * coefft[2];
	if (discriminant <= 0)
		return (0);
	root[0] = (-coefft[1] - sqrt(discriminant)) / (2.0 * coefft[0]);
	root[1] = (-coefft[1] + sqrt(discriminant)) / (2.0 * coefft[0]);
	set_closer_point(root, &ray, hit_record);
	if (v_length(v_sub(ray.origin, hit_record->origin)) <= EPSILON)
		return (0);
	hit_record->normal = v_unit(v_sub(hit_record->origin, sphere->center));
	hit_record->suface = object->surface;
	return (1);
}

// void	make_right_normal(t_ray *ray, t_plane *plane)
// {
// 	// 여기서 법선 벡터를 올바르게 만들어야 한다.
// 	if (plane->normal.e[1] == 1 || plane->normal.e[1] == -1)
// 	{
// 		// 카메라의 위치가 면의 점보다 아래면
// 		if (ray->origin.e[1] < plane->point.e[1])
// 			plane->normal.e[1] = -1;
// 		else
// 			plane->normal.e[1] = 1;
// 	}
// 	else if (plane->normal.e[2] == 1 || plane->normal.e[2] == -1)
// 	{
// 		if (ray->dir.e[2] >= EPSILON && plane->normal.e[2] >= EPSILON)
// 		{
// 			if (plane->normal.e[2] == 1)
// 				plane->normal.e[2] = -1;
// 			else
// 				plane->normal.e[2] = 1;
// 		}
// 	}
// }

int	hit_by_plane(t_ray ray, t_object *object, t_record *hit_record)
{
	// 만나는지
	//   면의 수직인 벡터가 ray에도 수직인지
	double		discriminant;
	double		root;
	t_plane		*plane;

	plane = (t_plane *)(object)->equation;
	// make_right_normal(&ray, plane);
	// 수직이거나 안 만날 때
	discriminant = v_dot(plane->normal, ray.dir);
	if (fabs(discriminant) < EPSILON)
		return (0);
	root = v_dot(v_sub(plane->point, ray.origin), plane->normal) / discriminant;
	hit_record->origin = v_add(ray.origin, v_mul_scalar(ray.dir, root));
	hit_record->normal = plane->normal;
	set_face_normal(ray, hit_record);
	hit_record->suface = object->surface;
	return (1);
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

void	update_hit_record(t_ray *ray, t_record *main, t_record *cmp)
{
	// main보다 cmp가 가깝다면
	if (v_length_squared(v_sub(ray->origin, main->origin))
		> v_length_squared(v_sub(ray->origin, cmp->origin)))
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
			update_hit_record(&ray, hit_record, &cmp);
			hit_surface = 1;
		}
		index++;
	}
	return (hit_surface);
}
