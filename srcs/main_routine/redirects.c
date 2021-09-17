/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:34:18 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 15:40:53 by jbenjy           ###   ########.fr       */
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

static void	redirect_more(int *old_out, int *old_in, int file, t_redirect *list)
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

int	redirect_exec(t_raw *root, int *old_out, int *old_in)
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
			redirect_more(old_out, old_in, file, list);
		list = list->next;
	}
	return (0);
}
