/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:52:10 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/11 16:21:35 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len(int n)
{
	int count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	int		len_n;
	char	*arr;

	len_n = len(n);
	if (!(arr = malloc(sizeof(char) * (len_n + 1))))
		return (0);
	arr[len_n] = '\0';
	if (n == 0)
		arr[0] = '0';
	if (n < 0)
	{
		arr[0] = '-';
		arr[--len_n] = n % 10 * (-1) + '0';
		n /= 10 * (-1);
	}
	while (n)
	{
		arr[--len_n] = n % 10 + '0';
		n /= 10;
	}
	return (arr);
}
