#include "minishell.h"

static	size_t	env_len(char *env)
{
	size_t i;

	i = 0;
	while(env[i] != '=' && env[i])
		i++;
	return(i);
}

int		my_unset(t_vars *vars, t_raw *root)
{
	t_envp_list	*env;
	t_envp_list	*env_iter;
	t_envp_list	*prev;

	env = vars->envp;
	env_iter = env;
	prev = env;
	if (ft_strncmp(root->command, "unset", 6) == 0 && root->flags == NULL && root->treated_comnd == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (1);
	}
	while (env_iter != NULL)
	{
		if (ft_strncmp(root->treated_comnd->arg, env_iter->key, env_len(env_iter->key)) == 0)
		{
			if (env_iter == env)
			{
				env = env_iter->next;
				free(env_iter);
				if (root->treated_comnd->next == NULL)
					break;
				root->treated_comnd = root->treated_comnd->next;
				env_iter = env;
			}
			else if (env_iter->next == NULL)
			{
				prev->next = NULL;
				free(env_iter);
				if (root->treated_comnd->next == NULL)
					break;
				root->treated_comnd = root->treated_comnd->next;
				env_iter = env;
			}
			else
			{
				prev->next = env_iter->next;
				free(env_iter);
				if (root->treated_comnd->next == NULL)
					break;
				root->treated_comnd = root->treated_comnd->next;
				env_iter = env;
			}
		}
		if (env_iter != env)
			prev = prev->next;
		env_iter = env_iter->next;
	}
	return (0);
}
