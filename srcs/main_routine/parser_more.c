/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:01:30 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 15:08:06 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command(char *str, t_raw *commands)
{
	int	i;

	i = 0;
	while (str[i] && !is_space(str[i]) && !is_special(str[i]))
		i++;
	commands->command = ft_strndup(str, i);
	return (str + i);
}

char	*find_flags(char *str, t_raw *command)
{
	int	i;

	i = 0;
	str = skip_spaces(str);
	if (!ft_strncmp("-", str, 1))
	{
		while (str[i] && !is_space(str[i]) && !is_special(str[i]))
			i++;
		command->flags = ft_strndup(str, i);
	}
	return (str + i);
}

char	*find_arg(char *str, t_raw *commands)
{
	int		curr;
	char	c;

	curr = 0;
	str = skip_spaces(str);
	while (str[curr] && !is_special(str[curr]))
	{
		if (str[curr] == '\'' || str[curr] == '\"')
		{
			while (str[curr] && (str[curr] == '\'' || str[curr] == '\"'))
			{
				c = str[curr++];
				while (str[curr] && str[curr] != c)
					curr++;
				curr++;
			}
		}
		curr++;
	}
	commands->argument = ft_strndup(str, curr);
	return (str + curr);
}
