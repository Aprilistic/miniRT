/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:12:54 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/12 14:12:55 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d_tmp;
	const unsigned char	*s_tmp;

	i = -1;
	d_tmp = (unsigned char *)dst;
	s_tmp = (const unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (dst <= src)
		while (++i < len)
			d_tmp[i] = s_tmp[i];
	else
		while (len--)
			d_tmp[len] = s_tmp[len];
	return (dst);
}
