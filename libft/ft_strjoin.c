/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:33:05 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/11 16:16:42 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	one_len;
	size_t	two_len;

	if (!s1 || !s2)
		return (0);
	one_len = ft_strlen(s1);
	two_len = ft_strlen(s2);
	ret = (char *)ft_calloc(one_len + two_len + 1, sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, s1, one_len);
	ft_memcpy(&ret[one_len], s2, two_len);
	return (ret);
}
