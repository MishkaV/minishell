/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:34:18 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/15 22:06:26 by jbenjy           ###   ########.fr       */
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
		}
		list = list->next;
	}
	return (status);
}