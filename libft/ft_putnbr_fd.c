/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:03:13 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/11 15:21:30 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char c;
	long num;

	num = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (num / 10)
		ft_putnbr_fd(num / 10, fd);
	c = num % 10 + '0';
	write(fd, &c, 1);
}
