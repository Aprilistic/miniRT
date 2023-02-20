/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:19:29 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/20 20:39:56 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset(char ch, char *charset)
{
	while (*charset != '\0')
	{
		if (ch == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	get_len4(char *str, char *charset, int flag)
{
	int	len;

	len = 0;
	if (flag)
		while (!is_charset(str[len], charset) && str[len])
			len++;
	else
		while (is_charset(str[len], charset) && str[len])
			len++;
	return (len);
}

int	get_word_cnt(char *str, char *charset)
{
	int	cnt;

	if (*charset == '\0')
		return (1);
	cnt = 0;
	while (*str)
	{
		if (!is_charset(*str, charset) && \
				(is_charset(*(str + 1), charset) || !*(str + 1)))
			cnt++;
		str++;
	}
	return (cnt);
}

void	ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	if (n != 0)
		dest[i] = '\0';
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	int		word_len;
	int		word_cnt;
	char	**arr;

	i = -1;
	j = 0;
	word_cnt = get_word_cnt(str, charset);
	arr = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	while (++i < word_cnt)
	{
		while (is_charset(str[j], charset))
			j++;
		word_len = get_len4(&str[j], charset, 1);
		arr[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		ft_strncpy(arr[i], &str[j], (unsigned int)word_len);
		j += word_len;
		j += get_len4(&str[j], charset, 0);
	}
	arr[word_cnt] = 0;
	return (arr);
}
