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

void	camera_location_move(t_mlx *mlx, int keycode)
{
	t_vec3	*cam_location;
	t_vec3	horizontal_dir;
	t_vec3	vertical_dir;

	cam_location = &mlx->camera.origin;
	horizontal_dir = v_cross(v_init(0, 1, 0), mlx->camera.dir);
	horizontal_dir = v_unit(horizontal_dir);
	vertical_dir = v_cross(mlx->camera.dir, horizontal_dir);
	vertical_dir = v_unit(vertical_dir);
	if (keycode == LEFT_ARROW_KEY)
		*cam_location = v_sub(*cam_location, horizontal_dir);
	else if (keycode == RIGHT_ARROW_KEY)
		*cam_location = v_add(*cam_location, horizontal_dir);
	else if (keycode == DOWN_ARROW_KEY)
		*cam_location = v_sub(*cam_location, mlx->camera.dir);
	else if (keycode == UP_ARROW_KEY)
		*cam_location = v_add(*cam_location, mlx->camera.dir);
	else if (keycode == PAGE_UP_KEY)
		*cam_location = v_add(*cam_location, vertical_dir);
	else if (keycode == PAGE_DOWN_KEY)
		*cam_location = v_sub(*cam_location, vertical_dir);
}
