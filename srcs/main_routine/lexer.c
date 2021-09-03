/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/03 20:35:58 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_default_command(char *command)
{	
	char *curr;
	curr = ft_tolower_str(command);
	puts(curr);
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
	free(curr);
	return (0);
}


char    *lexer_check_command(t_raw *root, t_vars *vars)
{
	(void)vars;

	while (root)
	{
		printf("Command: %d\n", check_default_command(root->command));
		root = root->next;
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