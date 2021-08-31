/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:24:50 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 22:43:46 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect  *rct_get_last(t_redirect  *root)
{
	if (!root)
		return (0);
	while (root->next)
		root = root->next;
	return (root);
}

t_redirect  *rct_new_node()
{
	t_redirect *curr;

	curr = malloc(sizeof(t_redirect));
	if (!curr)
		return (0);
	curr->file = 0;
	curr->type = 0;
	curr->next = 0;
	return (curr);
}

t_redirect	*rct_push(t_redirect *root, t_redirect *new_node)
{
	t_redirect *to_return;
	
	to_return = root;
	if (!root)
		return (new_node);
	root = rct_get_last(root);
	root->next = new_node;
	return (to_return);
}

void	rct_print(t_redirect *root)
{
	if (root)
	{
		while (root)
		{
			printf("Type: |%d|\n", root->type);
			printf("File: |%s|\n", root->file);
			root = root->next;	
		}
	}
	else
		printf("Redirects are empty\n");
}