/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:54 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/09 19:18:49 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(long long n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int			i;
	int			size;
	char		*ret;
	long long	num;

	i = 0;
	num = (long long)n;
	size = get_size(num);
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	if (!ret)
		return (0);
	if (num < 0)
	{
		ret[0] = '-';
		num *= -1;
		i++;
	}
	while (size - i)
	{
		ret[--size] = num % 10 + '0';
		num /= 10;
	}
	return (ret);
}
