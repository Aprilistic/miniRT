#include "../function.h"
#include "../macro.h"
#include "../struct.h"
#include <math.h>

t_vec3	focal_vector(t_camera *camera)
{
	t_vec3	dir;

	dir = v_unit(camera->dir);
	dir = v_mul_scalar(camera->dir, atan(camera->fov / 2.0) * (X_SIZE / 2));
	return (dir);
}

t_vec3	cam_offset_vector(t_vec3 *u, t_vec3 *v, int x, int y)
{
	t_vec3	x_dir;
	t_vec3	y_dir;

	x_dir = v_mul_scalar(*u, x - X_SIZE / 2);
	y_dir = v_mul_scalar(*v, y - Y_SIZE / 2);
	return (v_add(x_dir, y_dir));
}
