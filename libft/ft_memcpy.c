/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:10:45 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/12 14:10:48 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d_tmp;
	const unsigned char	*s_tmp;

	i = -1;
	if (!dst && !src)
		return (0);
	d_tmp = (unsigned char *)dst;
	s_tmp = (const unsigned char *)src;
	while (++i < n)
		d_tmp[i] = s_tmp[i];
	return (dst);
}
