/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:30:55 by lsinistr          #+#    #+#             */
/*   Updated: 2021/09/17 12:48:24 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_envp_list	*envp_pop_by_key_more(t_envp_list *root, char *key)
{
	t_envp_list	*to_return;
	t_envp_list	*prev;
	t_envp_list	*curr;

	to_return = root;
	prev = 0;
	curr = root;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (!prev)
				to_return = curr->next;
			else
				prev->next = curr->next;
			envp_free_node(curr);
			return (to_return);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

t_envp_list	*envp_pop_by_key(t_envp_list *root, char *key)
{
	if (!root)
		return (0);
	else
		return (envp_pop_by_key_more(root, key));
	return (0);
}

void	envp_print_list(t_envp_list	*root)
{
	if (!root)
		return ;
	while (root)
	{
		printf("Key: %s, data: %s\n", root->key, root->data);
		root = root->next;
	}
}

t_envp_list	*envp_copy_list(t_envp_list *root)
{
	t_envp_list	*new_list;

	new_list = 0;
	if (!root)
		return (0);
	while (root)
	{
		new_list = envp_push_node(new_list,
				ft_strdup(root->key), ft_strdup(root->data));
		root = root->next;
	}
	return (new_list);
}

int	envp_get_len(t_envp_list *root)
{
	int	count;

	count = 0;
	if (!root)
		return (0);
	while (root)
	{
		count++;
		root = root->next;
	}
	return (count);
}
