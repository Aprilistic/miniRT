#ifndef COLOR_H
# define COLOR_H

# include "vec3.h"

typedef struct s_color
{
	int		checkerboard;
	t_vec3	rgb;
	double	shineness;	
	double	brightness;
}	t_color;

#endif
