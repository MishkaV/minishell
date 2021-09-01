/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:20:59 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 13:21:52 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_quotes(char *str)
{
	int flag_q;
	int flag_dq;

	flag_q = 0;
	flag_dq = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (!flag_q)
				flag_q = 1;
			else
				flag_q = 0;	
		}
		else if (*str == '\"')
		{
			if (!flag_dq)
				flag_dq = 1;
			else
				flag_dq = 0;	
		}
		str++;
	}
	return (flag_dq || flag_q);
}

int	is_space(char c)
{
	return (c == '\t' || c == '\v' || c == '\r' ||
			c == '\f' || c == '\b' || c == ' ');
}