/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:35:04 by taeypark          #+#    #+#             */
/*   Updated: 2023/03/03 22:15:51 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "macro.h"
#include "function.h"

void	check_ratio(double ratio, int *errno)
{
	if (!(0 <= ratio && ratio <= 1.0))
		*errno |= RATE;
}

double	integer_part(char **str, int *errno)
{
	double	integer;

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

	if (**str == '.' && *(*str + 1) == '\0')
	{
		*errno |= NUM;
		return (0);
	}
	*str += (**str == '.');
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
	int		comma_cnt;
	char	**str_nums;

	if (*errno != OK)
		return (v_init(0, 0, 0));
	comma_cnt = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ',')
			comma_cnt++;
	if (comma_cnt != 2)
	{
		*errno |= NUM;
		return (v_init(0, 0, 0));
	}
	str_nums = ft_split(str, ",");
	i = -1;
	while (str_nums[++i])
		var.e[i] = atod(str_nums[i], errno);
	free_two_dimension(str_nums);
	*errno |= (i != 3) * NUM;
	return (var);
}
