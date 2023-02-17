/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:28:27 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/11 09:55:58 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ret;

	len = ft_strlen(s1);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, s1, len);
	return (ret);
}
