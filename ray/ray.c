#include "../includes/ray.h"

t_color	ray_color(const t_ray *r, const t_hittables *world, int depth)
{
	t_color	ret;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	if (depth <= 0)
		return (ret);
	if (world.hit())
	{
		//world hit 에서 새로운 ray 반환
		return (cos(radian)*ray_color(r, world, depth - 1));
	}
	return (constant * color + (1 - constant) * background_color);

}
