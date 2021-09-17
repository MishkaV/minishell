/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:20:36 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 13:21:15 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_check_command(t_raw *curr, t_vars *vars)
{
	int		command_code;
	char	*to_lower;
	int		flag;

	flag = 0;
	to_lower = ft_tolower_str(curr->command);
	command_code = lexer_check_default_command(to_lower);
	if (command_code == -1)
	{
		if (check_is_full_path_command(to_lower))
			command_code = COMMAND_FULL;
		else
			command_code = lexer_check_path_command(to_lower, vars);
		if (command_code == -1)
			flag = 1;
		curr->command_info.is_default = COMMAND_NOT_DEFAULT;
	}
	if (!ft_strlen(curr->command))
		curr->command_info.code = COMMAND_EMPTY;
	else
		curr->command_info.code = command_code;
	free(to_lower);
	return (flag);
}

int	lexer_check_flags(t_raw *curr)
{
	if (curr->flags)
	{
		if (curr->command_info.is_default == COMMAND_DEFAULT
			&& curr->command_info.code == COMMAND_ECHO
			&& !ft_strcmp(curr->flags, "-n"))
			return (0);
		return (1);
	}
	return (0);
}
