/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:25:18 by taeypark          #+#    #+#             */
/*   Updated: 2022/07/09 17:36:17 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr_fd_plus(int n, int fd)
{
	char	ch;

	if (n > 0)
		putnbr_fd_plus(n / 10, fd);
	else
		return ;
	ch = n % 10 + '0';
	ft_putchar_fd(ch, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n > 0)
		putnbr_fd_plus(n, fd);
	else
	{
		write(fd, "-", 1);
		putnbr_fd_plus(n * -1, fd);
	}
}
