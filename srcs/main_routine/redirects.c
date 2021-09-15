/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:34:18 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/15 23:03:24 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_file(char *str)
{
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
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
		if (list->type == SINGLE_IN)
			file = open(list->file, O_RDONLY, 0777);
		if (list->type == SINGLE_OUT)
			file = open(list->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		// if (list->type == DOUBLE_IN)
			// file = open(list->file, O_RDONLY, 0777); //here doc
		if (list->type == DOUBLE_OUT)
			file = open(list->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file == -1)
			return (print_error_file(list->file));
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