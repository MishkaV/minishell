/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:38:43 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 15:50:22 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_empty(void)
{
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `newline'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (-2);
}

static void	here_doc_more(t_redirect *list, int file)
{
	char	*str;

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
}

int	here_doc(t_redirect	*list)
{
	int		file;

	if (!ft_strlen(list->file))
		return (print_error_empty());
	file = open("./temporary/temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return (file);
	here_doc_more(list, file);
	close(file);
	return (open("./temporary/temp", O_RDONLY, 0777));
}

int	open_file(t_redirect	*list)
{
	int	file;

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
