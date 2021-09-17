/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 21:16:07 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:35:43 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_free_node(t_envp_list *node)
{
	if (!node)
		return (0);
	if (node->key)
		free(node->key);
	if (node->data)
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
		if (node->command)
			free(node->command);
		if (node->flags)
			free(node->flags);
		if (node->argument)
			free(node->argument);
		if (node->redirects)
			rct_free_list(node->redirects);
		if (node->treated_comnd)
			trls_free_list(node->treated_comnd);
		free(node);
	}
}

void	raw_free_list(t_raw *root)
{
	t_raw	*next;

	if (!root)
		return ;
	while (root)
	{
		next = root->next;
		raw_free_node(root);
		root = next;
	}
}

void	rct_free_node(t_redirect *node)
{
	if (node)
	{
		if (node->file)
			free(node->file);
		free(node);
	}
}
