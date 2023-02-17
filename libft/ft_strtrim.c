/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:47:32 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/10 16:25:56 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;
	char	*ret;

	if (!s1 || !set)
		return (0);
	s = 0;
	e = ft_strlen(s1) - 1;
	while (is_set(s1[s], set) && s1[s])
		s++;
	while (is_set(s1[e], set) && s1 != &s1[e])
		e--;
	e++;
	if (e < s)
		e = s;
	ret = (char *)ft_calloc(e - s + 1, sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, &s1[s], e - s);
	return (ret);
}
