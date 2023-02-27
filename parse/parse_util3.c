#include "struct.h"
#include "macro.h"
#include "function.h"
// 15.235
//  integer -> 15
//  decimal -> 0 + 2
//   decimal -> 0.2 + 3
//    decimal -> 0.32 + 5
//  * decimal -> 5.32

double	integer_part(char **str, int *errno)
{
	double	integer;

	// 정수부 계산
	if (**str == '.')
		*errno |= NUM;
	integer = 0;
	while (**str && **str != '.')
	{
		if (!ft_isdigit(**str))
		{
			*errno |= NUM;
			break ;
		}
		integer = integer * 10 + (**str - '0');
		(*str)++;
	}
	return (integer);
}

double	decimal_part(char **str, int *errno)
{
	double	decimal;
	int		division_num;

	// "123." 만 들어왔을 때 처리
	// 여기서 str++이 된다. 그래서 .을 넘어간다.
	if (**str == '.' && *(*str + 1) == '\0')
	{
		*errno |= NUM;
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
			*errno |= NUM;
			break ;
		}
		decimal = decimal * 10 + (**str - '0');
		division_num++;
		(*str)++;
	}
	return (decimal / pow(10, division_num));
}

double	atod(char *str, int *errno)
{
	int		sign;
	double	result;

	result = 0;
	if (*errno != OK)
		return (result);
	if (str[0] == '\0' || (str[0] == '-' && str[1] == '\0'))
		*errno |= NUM;
	sign = 1 - (str[0] == '-') * 2;
	str += (sign == -1);
	result = sign * (integer_part(&str, errno) + decimal_part(&str, errno));
	if (*str != '\0')
		*errno |= NUM;
	return (result);
}

t_vec3	parse_three_double(char *str, int *errno)
{
	int		i;
	t_vec3	var;
	char	**str_nums;

	if (*errno != OK)
		return (v_init(0, 0, 0));
	str_nums = ft_split(str, ",");
	i = 0;
	while (str_nums[i])
	{
		var.e[i] = atod(str_nums[i], errno);
		i++;
	}
	free_two_dimension(str_nums);
	if (i != 3)
		*errno |= NUM;
	return (var);
}
