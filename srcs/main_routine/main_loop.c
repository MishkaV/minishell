/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:36:47 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/27 10:59:01 by jbenjy           ###   ########.fr       */
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

// char	*ft_concat(char *s1, char *s2)
// {
// 	char *str;
	
// 	str = malloc(sizeof(char) * (ft))
// }

void	main_loop()
{
	char *str;
	
	while (1)
	{
		str = readline("\033[0;32mcool_bash \033[0m>> "); //Проверить, надо ли чистить после readline
		if (check_quotes(str))
			puts("\033[0;31mError syntax:\033[0m bad number of quotes");
		add_history(str);
		// free(s);	
	}
}