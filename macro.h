/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:37:17 by jinheo            #+#    #+#             */
/*   Updated: 2023/03/02 19:37:18 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# define INF 1e9
# define PI 3.14159265359

# define EPSILON 1e-11
# define REFLECTION_CNT 3
# define LIGHT_ATTENUATION	50.0
# define MAX_DIST	200

/* parsing macros */
# define S_AMBIENT "A"
# define S_CAMERA "C"
# define S_LIGHT "L"
# define S_BACK "B"
# define S_SPHERE "sp"
# define S_PLANE "pl"
# define S_CYLINDER "cy"
# define S_CONE "co"
# define S_SPACES " \t\r\n\v\f"
# define OK 0
# define ERROR -1
# define ARG_CNT 7
# define CAP_CNT 3

enum	e_error
{
	ACCESS = 0,
	EXTENSION = 1,
	LENGTH = 2,
	FOV = 4,
	RATE = 8,
	UNIT = 16,
	RGB = 32,
	UNDEFINED = 64,
	OPTION_CNT = 128,
	NUM = 256,
	CAPITAL = 512
};

/* our_mlx macros */
# define Y_SIZE 720
# define X_SIZE 1280
# define WIN_NAME "miniRT"
# define DESTROY_ICON 17

enum	e_key
{
	ESC_KEY = 53,
	LEFT_ARROW_KEY = 123,
	RIGHT_ARROW_KEY,
	DOWN_ARROW_KEY,
	UP_ARROW_KEY,
	PAGE_UP_KEY = 116,
	PAGE_DOWN_KEY = 121
};

enum	e_mouse
{
	SCROLL_UP = 4,
	SCROLL_DOWN
};

/* shape macros */
enum	e_type
{
	CONE,
	PLANE,
	SPHERE,
	CYLINDER,
};

#endif
