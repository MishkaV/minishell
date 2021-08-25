/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:09:43 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/23 15:17:35 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_envp_list *envp_new_node(char *key, char *data)
{
	t_envp_list *curr;

	curr = malloc(sizeof(t_envp_list));
	if (!curr)
		return (0);
	
	curr->key = key;
	curr->data = data;
	curr->next = 0;
	return (curr);
}


t_envp_list *envp_push_node(t_envp_list *root, char *key, char *data)
{
	t_envp_list	*curr;
	
	if (!root)
		root = envp_new_node(key, data);
	else
	{
		curr = root;
		while(curr->next)
			curr = curr->next;
		curr->next = envp_new_node(key, data);
		if (!curr->next)
			return (0);
	}
	return (root);
}

char	*envp_get_data(t_envp_list *root, char *key)
{
	
	if (!root)
		return (0);
	else
	{
		while (root)
		{
			if (!ft_strcmp(root->key, key))
				return (root->data);
			root = root->next;
		}
	}
	return (0);
}


int	envp_change_data(t_envp_list *root, char *key, char *data)
{
	if (!root)
		return (0);
	else
	{
		while (root)
		{
			if (!ft_strcmp(root->key, key))
			{
				free(root->data);
				root->data = ft_strdup(data);
				return (1);
			}
			root = root->next;
		}
	}
	return (0);
}

t_envp_list *envp_pop_front(t_envp_list *root)
{
	t_envp_list	*curr;
	if (!root)
		return (0);
	else
	{
		curr = root->next;
		envp_free_node(root);
		root = curr;
	}
	return (root);
}

t_envp_list *envp_pop_by_key(t_envp_list *root, char *key)
{
	t_envp_list	*to_return;
	t_envp_list	*prev;
	t_envp_list	*curr;

	if (!root)
		return (0);
	else
	{
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
	}
	return (to_return);
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