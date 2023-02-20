/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:50:58 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/29 09:53:57 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	one_len;
	size_t	two_len;

	if (!s1 || !s2)
		return (0);
	one_len = 0;
	two_len = 0;
	while (s1[one_len])
		one_len++;
	while (s2[two_len])
		two_len++;
	ret = (char *)malloc(sizeof(char) * (one_len + two_len + 1));
	if (!ret)
		return (0);
	ft_memcpy(ret, s1, one_len);
	ft_memcpy(&ret[one_len], s2, two_len);
	ret[one_len + two_len] = '\0';
	free((void *)s1);
	return (ret);
}

char	*free_and_null(char **aim)
{
	if (*aim)
		free(*aim);
	*aim = 0;
	return (0);
}

char	*read_until_line(int fd, char *backup)
{
	char	*ret;
	int		read_ret;
	char	buf[BUFFER_SIZE + 1];

	if (backup)
		ret = backup;
	else
	{
		ret = ft_calloc(1, 1);
		if (!ret)
			return (0);
	}
	while (1)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret < 0)
			return (free_and_null(&ret));
		buf[read_ret] = '\0';
		ret = ft_strjoin(ret, buf);
		if (!ret || read_ret < BUFFER_SIZE || ft_strchr(ret, '\n'))
			break ;
	}
	return (ret);
}

char	*get_backup(char *start)
{
	char	*ret;
	size_t	start_len;

	start_len = 0;
	while (start[start_len])
		start_len++;
	ret = ft_substr(start, 0, start_len);
	if (!ret)
		return (0);
	*start = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*ret;
	char		*addr_of_nl;
	static char	*backup;

	if (fd < 0 || fd > MAX)
		return (0);
	ret = read_until_line(fd, backup);
	backup = 0;
	if (!ret || !*ret)
		return (free_and_null(&ret));
	addr_of_nl = ft_strchr(ret, '\n');
	if (addr_of_nl)
	{
		backup = get_backup(addr_of_nl + 1);
		if (!backup)
			return (0);
	}
	return (ret);
}
