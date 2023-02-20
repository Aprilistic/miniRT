#ifndef OUR_MLX_H
# define OUR_MLX_H
# define Y_SIZE 500
# define X_SIZE 500
# define WIN_NAME "miniRT"

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
}	t_mlx;

void	init_mlx(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
