#ifndef MACRO_H
# define MACRO_H

# define INF	1e9

/* parsing macros */
# define S_AMBIENT "A"
# define S_CAMERA "C"
# define S_LIGHT "L"
# define S_SPHERE "sp"
# define S_PLANE "pl"
# define S_CYLINDER "cy"
# define S_CONE "co"
# define S_SPACES " \t\r\n\v\f"
# define OK 0
# define ERROR -1

/* our_mlx macros */
# define Y_SIZE 500
# define X_SIZE 500
# define WIN_NAME "miniRT"
# define DESTROY_ICON 17
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

/* shape macros */
enum e_type {
  CONE,
  PLANE,
  SPHERE,
  CYLINDER,
};

#endif
