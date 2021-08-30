/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 21:16:07 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/30 17:40:29 by jbenjy           ###   ########.fr       */
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

void	raw_free_node(t_raw *node)
{
	if (node)
	{
		if(node->command)
			free(node->command);
		if(node->flags)
			free(node->flags);
		if(node->argument)
			free(node->argument);
		free(node);
	}
}

void	raw_free_list(t_raw *root)
{
	t_raw *next;

	while (root)
	{
		next = root->next;
		raw_free_node(root);
		root = next;		
	}
}
