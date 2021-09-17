/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:35:13 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 13:45:19 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_check_def_command_more(char *command)
{
	if (!ft_strcmp(command, "unset"))
		return (COMMAND_UNSET);
	if (!ft_strcmp(command, "env"))
		return (COMMAND_ENV);
	if (!ft_strcmp(command, "exit"))
		return (COMMAND_EXIT);
	return (-1);
}

int	lexer_check_default_command(char *command)
{	
	if (!ft_strcmp(command, "echo"))
		return (COMMAND_ECHO);
	if (!ft_strcmp(command, "cd"))
		return (COMMAND_CD);
	if (!ft_strcmp(command, "pwd"))
		return (COMMAND_PWD);
	if (!ft_strcmp(command, "export"))
		return (COMMAND_EXPORT);
	return (lexer_check_def_command_more(command));
}

static int	lexer_check_in_pwd(char *command)
{
	struct stat	buff;
	int			to_return;

	to_return = -1;
	if (stat(command, &buff) != -1 && !ft_strncmp(command, "./", 2))
		to_return = COMMAND_IN_PWD;
	return (to_return);
}

int	lexer_check_path_command(char *command, t_vars *vars)
{
	struct stat	buff;
	char		*path;
	char		*full_path;
	int			i;

	i = 0;
	while (vars->paths[i])
	{
		path = ft_concat("/", command);
		full_path = ft_concat(vars->paths[i], path);
		if (stat(full_path, &buff) != -1)
		{
			free(path);
			free(full_path);
			return (i);
		}
		free(path);
		free(full_path);
		i++;
	}
	return (lexer_check_in_pwd(command));
}

int	check_is_full_path_command(char *command)
{
	struct stat	buff;

	if (stat(command, &buff) != -1)
		return (1);
	return (0);
}
