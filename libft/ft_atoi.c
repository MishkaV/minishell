/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:13:42 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/11 16:21:26 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check(char c)
{
	if (c == '\t')
		return (0);
	if (c == '\v')
		return (0);
	if (c == '\f')
		return (0);
	if (c == '\r')
		return (0);
	if (c == '\n')
		return (0);
	if (c == ' ')
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	unsigned long	num;
	int				sign;

	num = 0;
	sign = 1;
	while (!check(*str) && *str)
		str++;
	if (*str == '-' && str[1] >= '0' && str[1] <= '9')
	{
		sign = -sign;
		str++;
	}
	if (*str == '+' && str[1] >= '0' && str[1] <= '9')
		str++;
	while (*str != '\0' && *str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	if (num > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (num * sign);
}
