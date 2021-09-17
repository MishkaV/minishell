/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:40:07 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:50:31 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	another_case(t_envp_list **current,
							t_envp_list **node, t_envp_list *env_iter)
{
	*current = env_iter;
	while ((*current)->next != NULL && ft_strncmp((*node)->key,
			(*current)->next->key, ft_strlen((*node)->key)
			+ ft_strlen((*current)->next->key)) > 0)
		(*current) = (*current)->next;
	(*node)->next = (*current)->next;
	(*current)->next = (*node);
}

static	t_envp_list	*sort_export(t_envp_list *envp)
{
	t_envp_list	*env_iter;
	t_envp_list	*node;
	t_envp_list	*current;

	env_iter = NULL;
	while (envp != NULL)
	{
		node = envp;
		envp = envp->next;
		if (env_iter == NULL || ft_strncmp(node->key, env_iter->key,
				ft_strlen(node->key) + ft_strlen(env_iter->key)) < 0)
		{
			node->next = env_iter;
			env_iter = node;
		}
		else
			another_case(&current, &node, env_iter);
	}
	return (env_iter);
}

int	my_export(t_vars *vars, t_raw *root)
{
	t_envp_list	*sort_env;
	t_envp_list	*begin;
	int			status;

	status = 0;
	if (!vars || !root)
		return (1);
	if (root->flags == NULL && root->treated_comnd == NULL)
	{
		sort_env = envp_copy_list(vars->envp);
		sort_env = sort_export(sort_env);
		begin = sort_env;
		while (sort_env != NULL)
		{
			printf ("declare -x %s=%s\n", sort_env->key, sort_env->data);
			sort_env = sort_env->next;
		}
		envp_free_list(begin);
	}
	else
		status = my_export_more(vars, root);
	return (status);
}
