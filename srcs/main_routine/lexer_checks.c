/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:35:13 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/12 22:05:59 by jbenjy           ###   ########.fr       */
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
	// if (!ft_strcmp(command, "./minishell")) // Надо поменять на недефолт в pwd
	// 	return (COMMAND_MINISHELL);
	return (-1);
}


int lexer_check_default_command(char *command)
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

int		lexer_check_path_command(char *command, t_vars *vars)
{
	struct stat buff;
	char	*path;
	char	*full_path;
	int		i;

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
	return (-1);
}

int	lexer_check_command(t_raw *curr, t_vars *vars)
{
	int	command_code;
	char *to_lower;
	int	flag;
	

	flag = 0;
	to_lower = ft_tolower_str(curr->command);
	command_code = lexer_check_default_command(to_lower);
	if (command_code == -1)
	{
		command_code = lexer_check_path_command(to_lower, vars);
		if (command_code == -1)
		{
			flag = 1;
			print_error(ERROR_NOT_FOUND);
		}
		curr->command_info.is_default = COMMAND_NOT_DEFAULT;
	}
	curr->command_info.code = command_code;
	free(to_lower);
	return(flag);
}

int	lexer_check_flags(t_raw *curr)
{
	if (curr->flags)
	{
		if (curr->command_info.is_default == COMMAND_DEFAULT &&
			curr->command_info.code == COMMAND_ECHO &&
			!ft_strcmp(curr->flags, "-n"))
				return (0);
		print_error(ERROR_BAD_FLAG);
		return (1);
	}
	return (0);
}