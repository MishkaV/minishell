#include "minishell.h"

static	void	another_case(t_envp_list **current, t_envp_list **node, t_envp_list *env_iter)
{
	*current = env_iter;
	while ((*current)->next != NULL && ft_strncmp((*node)->key, (*current)->next->key, ft_strlen((*node)->key) + ft_strlen((*current)->next->key)) > 0)
		(*current) = (*current)->next;
	(*node)->next = (*current)->next;
	(*current)->next = (*node);
}

static	t_envp_list	*sort_export(t_envp_list *envp)
{
	t_envp_list	*env_iter;
	t_envp_list *node;
	t_envp_list *current;

	env_iter = NULL;
	while (envp != NULL)
	{
		node = envp;
		envp = envp->next;
		if (env_iter == NULL || ft_strncmp(node->key, env_iter->key, ft_strlen(node->key) + ft_strlen(env_iter->key)) < 0)
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
	t_envp_list *sort_env;


	if (root->flags == NULL && root->treated_comnd == NULL)
	{
		sort_env = (*vars).envp;
		sort_env = sort_export(sort_env);
		while (sort_env != NULL)
		{
			printf ("declare -x %s=%s\n", sort_env->key, sort_env->data);
			sort_env = sort_env->next;
		}
	}
	//else
	//{
		// if (root->treated_comnd->arg)
		// {
		// 	printf("declare -x %s=\n", root->treated_comnd->arg);
		// }
		// root->treated_comnd = root->treated_comnd->next;
	//}
	return (0);
}