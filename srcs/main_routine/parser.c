/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:55:05 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/03 12:56:45 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command(char *str, t_raw *commands)
{
	int i;

	i = 0;
	while (str[i] && !is_space(str[i]) && !is_special(str[i]))
		i++;
	commands->command = ft_strndup(str, i);
	return (str + i);
}

char	*find_flags(char *str, t_raw *command)
{
	int i;

	i = 0;
	str = skip_spaces(str);
	if (!ft_strncmp("-n", str, 2))
	{
		command->flags = ft_strndup("-n", 2);
		i += 3;
	}
	return (str + i);
}

char	*find_arg(char *str, t_raw *commands)
{
	int	curr;

	curr = 0;
	str = skip_spaces(str);
	while (str[curr] && !is_special(str[curr]))
		curr++;
	commands->argument = ft_strndup(str, curr);
	return (str + curr);
}

char	*find_pipe(char *str, t_raw *command, int *check_type)
{
	int i;
	t_redirect *curr_rct;

	while (*str && is_special(*str))
	{
		i = 0;
		if (*str == '|' || *str == ';')
		{
			if (*str == '|')
				*check_type = TYPE_PIPE;
			return (str + 1);
		}
			
		curr_rct = rct_new_node();
		str = check_rct(curr_rct, str);
		str = skip_spaces(str);
		while (str[i] && !is_special(str[i]))
			i++;
		
		curr_rct->file = ft_strndup(str, i);
		command->redirects = rct_push(command->redirects, curr_rct);
		str += i;
	}
	return (str);
}
