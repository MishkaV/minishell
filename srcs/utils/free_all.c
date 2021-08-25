/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 21:16:07 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/23 15:17:52 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_free_node(t_envp_list *node)
{
	if (!node)
		return (0);
	free(node->key);
	free(node->data);
	free(node);
	return (1);
}

int	envp_free_list(t_envp_list *root)
{
	t_envp_list	*next;
	
	if (!root)
		return (0);
	while (root)
	{
		next = root->next;
		envp_free_node(root);
		root = next;	
	}
	return (1);
}
