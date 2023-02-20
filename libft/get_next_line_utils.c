/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:52:26 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/18 16:20:32 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)b;
	while (i < len)
		tmp[i++] = (unsigned char)c;
	return (b);
}

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return (ft_calloc(1, sizeof(char)));
	if (s_len - start < len)
		len = s_len - start;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[len] = '\0';
	return ((char *)ft_memcpy(ret, &s[start], len));
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char		ch;
	const unsigned char	*str;

	ch = (unsigned char)c;
	str = (const unsigned char *)s;
	while (*str)
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == 0)
		return ((char *)str);
	return (0);
}
