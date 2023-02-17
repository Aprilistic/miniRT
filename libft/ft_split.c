/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 09:33:14 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/10 17:53:54 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_cnt(char const *str, char c)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c && (*(str + 1) == c || !*(str + 1)))
			cnt++;
		str++;
	}
	return (cnt);
}

static int	get_len(char const *str, char c, int flag)
{
	int	len;

	len = 0;
	if (flag)
		while (str[len] == c && str[len])
			len++;
	else
		while (str[len] != c && str[len])
			len++;
	return (len);
}

static char	*make_copy(const char *s, int len)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, s, len);
	return (ret);
}

static char	**free_2d(char **arr, int cnt)
{
	int	i;

	i = -1;
	while (++i < cnt)
		free(arr[i]);
	free(arr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		word_len;
	int		word_cnt;
	char	**arr;

	i = -1;
	j = 0;
	if (!s)
		return (0);
	word_cnt = get_word_cnt(s, c);
	arr = (char **)ft_calloc(word_cnt + 1, sizeof(char *));
	if (!arr)
		return (0);
	while (++i < word_cnt)
	{
		while (s[j] == c && s[j])
			j++;
		word_len = get_len(&s[j], c, 0);
		arr[i] = make_copy(&s[j], word_len);
		if (!arr[i])
			return (free_2d(arr, i));
		j += word_len;
	}
	return (arr);
}
