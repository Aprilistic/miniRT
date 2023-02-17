/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:31:51 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/12 09:37:25 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t				len;
	unsigned char		ch;
	const unsigned char	*str;

	len = ft_strlen(s);
	ch = (unsigned char)c;
	str = (const unsigned char *)(s + len - 1);
	if (ch == 0)
		return ((char *)(str + 1));
	while (len--)
	{
		if (*str == ch)
			return ((char *)str);
		str--;
	}
	return (0);
}
