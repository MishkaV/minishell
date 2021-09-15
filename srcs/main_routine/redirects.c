/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:34:18 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/15 18:52:01 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     redirect_exec(t_raw *root, int *old_out, int *old_in)
{
	t_redirect	*list;
	int			file;
	int			status;	
	//Подумать про старые


	list = root->redirects;
	status = 0;
	(void)old_out;
	(void)old_in;

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
			status = 1;
		else
		{
			// dup2(*old_in, STDIN_FILENO);
			// dup2(*old_out, STDOUT_FILENO);
			
			if (list->type == SINGLE_OUT || list->type == DOUBLE_OUT)
			{
				dup2(file, STDOUT_FILENO);
				close(file);
			}
			// else
			// 	dup2(file, STDIN_FILENO);
		}
		list = list->next;
	}
	return (status);
}