/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:34:18 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/16 22:03:40 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_file(char *str)
{
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("no such file or this is directory: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

static int	print_error_empty(void)
{
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `newline'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (-2);
}

static int here_doc(t_redirect	*list)
{
	int file;
	char	*str;

	if (!ft_strlen(list->file))
		return (print_error_empty());
	file = open("./temporary/temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return (file);
	while (1)
	{
		str = readline("heredoc> ");
		if (!str)
			break ;
		else
		{
			if (!ft_strcmp(str, list->file))
			{
				free(str);
				break ;
			}
			ft_putstr_fd(str, file);
			ft_putstr_fd("\n", file);
			free(str);	
		}
	}
	close(file);
	return (open("./temporary/temp", O_RDONLY, 0777));
}

static int open_file(t_redirect	*list)
{
	int file;

	file = -1;
	if (list->type == SINGLE_IN)
		file = open(list->file, O_RDONLY, 0777);
	if (list->type == SINGLE_OUT)
		file = open(list->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (list->type == DOUBLE_IN)
		file = here_doc(list);
	if (list->type == DOUBLE_OUT)
		file = open(list->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (file);
}

int     redirect_exec(t_raw *root, int *old_out, int *old_in)
{
	t_redirect	*list;
	int			file;

	list = root->redirects;
	if (!list)
		return (0);
	while (list)
	{
		file = open_file(list);
		if (file == -1)
			return (print_error_file(list->file));
		else if (file == -2)
			return (1);
		else
		{
			if (list->type == SINGLE_OUT || list->type == DOUBLE_OUT)
			{
				*old_out = dup(STDOUT_FILENO);
				dup2(file, STDOUT_FILENO);
			}
			else
			{	
				*old_in = dup(STDIN_FILENO);
				dup2(file, STDIN_FILENO);
			}
			close(file);
		}
		list = list->next;
	}
	return (0);
}