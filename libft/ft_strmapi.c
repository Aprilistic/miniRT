/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:39:05 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/12 09:36:57 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ret;
	size_t	s_len;

	if (!s || !f)
		return (0);
	i = -1;
	s_len = ft_strlen(s);
	ret = (char *)ft_calloc(s_len + 1, sizeof(char));
	if (!ret)
		return (0);
	while (s[++i])
		ret[i] = f(i, s[i]);
	return (ret);
}
