#include "struct.h"
#include "macro.h"
#include "function.h"
#include <stdlib.h>
#include <fcntl.h>
// 15.235
//  integer -> 15
//  decimal -> 0 + 2
//   decimal -> 0.2 + 3
//    decimal -> 0.32 + 5
//  * decimal -> 5.32

double	integer_part(char **str, int *status)
{
	double	integer;
	int		sign;

	// 정수부 계산
	sign = 1 - (**str == '-') * 2;
	*str += (sign == -1);
	integer = 0;
	while (**str && **str != '.')
	{
		if (!ft_isdigit(**str))
		{
			*status = ERROR;
			break ;
		}
		integer = integer * 10 + (**str - '0');
		(*str)++;
	}
	return (sign * integer);
}

double	decimal_part(char **str, int *status)
{
	double	decimal;
	int		division_num;

	// "123." 만 들어왔을 때 처리
	// 여기서 str++이 된다. 그래서 .을 넘어간다.
	if (**str == '.' && *(*str + 1) == '\0')
	{
		*status = ERROR;
		return (0);
	}
	*str += (**str == '.');
	// 소수부 계산
	decimal = 0;
	division_num = 0;
	while (**str)
	{
		if (!ft_isdigit(**str))
		{
			*status = ERROR;
			break ;
		}
		decimal = decimal * 10 + (**str - '0');
		division_num++;
		(*str)++;
	}
	return (decimal / pow(10, division_num));
}

double	atod(char *str, int *status)
{
	return (integer_part(&str, status) + decimal_part(&str, status));
}

double	parse_atod(char **str, int *status)
{
	return (integer_part(str, status) + decimal_part(str, status));
}

t_vec3	parse_three_double(char *str, int *status)
{
	t_vec3	var;

	var.e[0] = parse_atod(&str, status);
	if (*status == ERROR && *str == ',')
	{
		str++;
		*status = OK;
	}

	var.e[1] = parse_atod(&str, status);
	if (*status == ERROR && *str == ',')
	{
		str++;
		*status = OK;
	}

	var.e[2] = parse_atod(&str, status);

	return (var);
}
