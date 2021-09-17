/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:35:29 by lsinistr          #+#    #+#             */
/*   Updated: 2021/09/17 12:35:57 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rct_free_list(t_redirect *root)
{
	t_redirect	*next;

	if (!root)
		return ;
	while (root)
	{
		next = root->next;
		rct_free_node(root);
		root = next;
	}
}

void	trls_free_list(t_trls *root)
{
	t_trls	*next;

	if (root)
	{
		while (root)
		{
			next = root->next;
			if (root->arg)
				free(root->arg);
			free(root);
			root = next;
		}
	}
}
