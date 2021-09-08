/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/08 13:34:00 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_def_command_more(char *command)
{
	if (!ft_strcmp(command, "unset"))
		return (COMMAND_UNSET);
	if (!ft_strcmp(command, "env"))
		return (COMMAND_ENV);
	if (!ft_strcmp(command, "exit"))
		return (COMMAND_EXIT);
	if (!ft_strcmp(command, "./minishell"))
		return (COMMAND_MINISHELL);
	return (-1);
}


int check_default_command(char *command)
{	
	if (!ft_strcmp(command, "echo"))
		return (COMMAND_ECHO);	
	if (!ft_strcmp(command, "cd"))
		return (COMMAND_CD);
	if (!ft_strcmp(command, "pwd"))
		return (COMMAND_PWD);
	if (!ft_strcmp(command, "export"))
		return (COMMAND_EXPORT);
	return (check_def_command_more(command));
}

int		check_path_command(char *command, t_vars *vars)
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

char    *lexer_check_command(t_raw *curr, t_vars *vars)
{
	(void)vars;
	int	command_code;
	char *to_lower;
	

	to_lower = ft_tolower_str(curr->command);
	command_code = check_default_command(to_lower);
	if (command_code == -1)
	{	
		command_code = check_path_command(to_lower, vars);
		
		if (command_code == -1)
			print_error(ERROR_NOT_FOUND);
	}

	
	free(to_lower);
	return (0);
}


t_raw   *lexer_analysis(t_raw *root, t_vars *vars)
{
	
	// struct stat buff;
	// (void)root;
	// stat("/bin", &buff);
	// printf("%lld\n", buff.st_size);
	lexer_check_command(root, vars);
	
	return (0);
}