/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:32:14 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/12 15:28:41 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (size && (size * count) / size != count)
		return (0);
	ret = malloc(size * count);
	if (!ret)
		return (0);
	return (ft_memset(ret, 0, size * count));
}
