/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:20:59 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/10 11:00:43 by jbenjy           ###   ########.fr       */
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
		if (*str == '\\' && *(str + 1) == '\"')
			str++;
		else if (*str == '\'')
		{
			if (!flag_q)
				flag_q = 1;
			else
				flag_q = 0;	
		}
		else if (*str == '\"')
			flag_dq++;
		str++;
	}
	return (flag_dq % 2 || flag_q);
}

int	is_dequote(char c)
{
	return (c == '\"' || c == '\\');
}

int	is_space(char c)
{
	return (c == '\t' || c == '\v' || c == '\r' ||
			c == '\f' || c == '\b' || c == ' ');
}


int	is_special(char c)
{
	return (c == '|' || c == ';' || c == '<' || c == '>');
}

char	*check_rct(t_redirect *curr_rct, char *str)
{
	if (*str == '<')
	{
		if (!ft_strncmp(str, "<<", 2))
			curr_rct->type = DOUBLE_IN;
		else
			curr_rct->type = SINGLE_IN;
	}
	else
	{
		if (!ft_strncmp(str, ">>", 2))
			curr_rct->type = DOUBLE_OUT;
		else
			curr_rct->type = SINGLE_OUT;
	}
	while (*str && (*str == '<' || *str == '>'))
		str++;
	return (str);
}
