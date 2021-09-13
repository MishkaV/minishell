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

static int	print_not_valid(char *str)
{
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (1);
}

static void	my_export_push_node(t_trls *list, t_vars *vars)
{
	char		*key;
	char		*data;

	key = ft_strndup(list->arg, ft_find_chr(list->arg, '='));
	if (!key)
		key = ft_strdup("");
	data = ft_strdup(ft_strchr(list->arg, '=') + 1);
	if (!data)
		data = ft_strdup("");
	if (envp_get_data(vars->envp, key))
	{
		envp_change_data(vars->envp, key, data);
		free(key);
	}
	else
		vars->envp = envp_push_node(vars->envp, key, data);
}

static int	my_export_more(t_vars *vars, t_raw *root)
{
	t_trls		*list;
	int			status;

	list = root->treated_comnd;
	status = 0;
	while (list)
	{
		if (list->arg[0] == '=' && !status)
			status = print_not_valid(list->arg);
		else if (list->arg[0] != '=' && ft_strchr(list->arg, '='))
			my_export_push_node(list, vars);
		list = list->next;
	}
	return (status);
}

int	my_export(t_vars *vars, t_raw *root)
{
	t_envp_list *sort_env;
	t_envp_list *begin;
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
