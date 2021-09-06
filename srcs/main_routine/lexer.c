/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/06 20:09:57 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_def_command_more(char *command)
{
	char	*curr;

	curr = ft_tolower_str(command);
	if (!ft_strcmp(curr, "unset"))
	{
		free(curr);
		return (COMMAND_UNSET);
	}
	if (!ft_strcmp(curr, "env"))
	{
		free(curr);
		return (COMMAND_ENV);
	}
	if (!ft_strcmp(curr, "exit"))
	{
		free(curr);
		return (COMMAND_EXIT);
	}
	if (!ft_strcmp(curr, "./minishell"))
	{
		free(curr);
		return (COMMAND_MINISHELL);
	}
	free(curr);
	return (-1);
}


int check_default_command(char *command)
{	
	char	*curr;

	curr = ft_tolower_str(command);
	if (!ft_strcmp(curr, "echo"))
	{
		free(curr);
		return (COMMAND_ECHO);	
	}
	if (!ft_strcmp(curr, "cd"))
	{
		free(curr);
		return (COMMAND_CD);
	}
	if (!ft_strcmp(curr, "pwd"))
	{
		free(curr);
		return (COMMAND_PWD);
	}
	if (!ft_strcmp(curr, "export"))
	{
		free(curr);
		return (COMMAND_EXPORT);
	}
	free(curr);
	return (check_def_command_more(command));
}

int		check_path_command(char *command, t_vars *vars)
{
	struct stat buff;
	char	*curr;
	char	*path;
	char	*full_path;
	int		i;

	curr = ft_tolower_str(command);
	i = 0;
	while (vars->paths[i])
	{
		path = ft_concat("/", curr);
		full_path = ft_concat(vars->paths[i], path);
		if (stat(full_path, &buff) != -1)
		{
			free(path);
			free(full_path);
			free(curr);
			return (i);
		}
		free(path);
		free(full_path);
		i++;
	}
	free(curr);
	return (-1);
}

char    *lexer_check_command(t_raw *curr, t_vars *vars)
{
	(void)vars;
	int	command_code;

	command_code = check_default_command(curr->command);
	if (command_code == -1)
	{	
		command_code = check_path_command(curr->command, vars);
		
		if (command_code == -1)
			print_error(ERROR_NOT_FOUND);	
		// printf("%s\n",vars->paths[command_code]);	
	}
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