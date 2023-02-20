#ifndef OUR_MLX_H
# define OUR_MLX_H
# define Y_SIZE 500
# define X_SIZE 500
# define WIN_NAME "miniRT"
# define DESTROY_ICON 17
# include "hittable.h"

enum	e_key
{
	S_KEY = 1,
	ESC_KEY = 53,
	LEFT_ARROW_KEY = 123,
	RIGHT_ARROW_KEY,
	DOWN_ARROW_KEY,
	UP_ARROW_KEY
};

enum	e_mouse
{
	LEFT = 1,
	SCROLL_UP = 4,
	SCROLL_DOWN
};

/* image structure */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/* mlx structure */
typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		img;
	t_hittable	*obj_list;
}	t_mlx;

void	init_mlx(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_mlx *mlx);
int		destroy_window(t_mlx *mlx);
void	minirt_hook(t_mlx *mlx);

#endif
