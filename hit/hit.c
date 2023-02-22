#include "../struct.h"
#include "../macro.h"
#include "../function.h"

int	hit_by_sphere(t_ray ray, t_object *t_object, t_record *hit_record)
{
	// P(t) = A + bt
	//        A : 광선, b : 광선의 방향
	// 이차 방정식 𝑡^2𝐛⋅𝐛+2𝑡𝐛⋅(𝐀−𝐂)+(𝐀−𝐂)⋅(𝐀−𝐂)−𝑟^2=0
	//          at^2 + bt + c = 0
	//          a = 𝐛⋅𝐛;
	//          b = 2 * 𝐛⋅(𝐀−𝐂)
	//          c = (𝐀−𝐂)⋅(𝐀−𝐂)−𝑟^2
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	save;

	a = v_dot(ray.dir, ray.dir);
	save = v_sub(ray.origin, sphere->center); //(A-C)
	b = 2 * v_dot(ray.dir, save);
	c = v_dot(save, save) - pow(sphere->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant <= 0)
		return (0);
	hit_record->origin = ray.origin + ray.dir * (/* 근 */);
	hit_record->normal = 
	hit_record->suface = 
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