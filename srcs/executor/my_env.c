#include "minishell.h"

static	int	check_pwd_args(t_raw *root)
{
	return (((ft_strncmp(root->treated_comnd->arg, "pwd", 4) == 0 || ft_strncmp(root->treated_comnd->arg, "PWD", 4) == 0) && root->treated_comnd->next == NULL)
		|| ((ft_strncmp(root->treated_comnd->arg, "pwd", 4) == 0 || ft_strncmp(root->treated_comnd->arg, "PWD", 4) == 0)
		&& ft_strncmp(root->treated_comnd->next->arg, "-L", 3) == 0 && root->treated_comnd->next->next == NULL)
		|| ((ft_strncmp(root->treated_comnd->arg, "pwd", 4) == 0 || ft_strncmp(root->treated_comnd->arg, "PWD", 4) == 0)
		&& ft_strncmp(root->treated_comnd->next->arg, "-P", 3) == 0 && root->treated_comnd->next->next == NULL));
}

int		my_env(t_vars vars, t_raw *root)
{
	t_envp_list	*env;
	t_envp_list *env_iter;
	char		*get_pwd;
	struct stat var_stat;

	env = vars.envp;
	env_iter = env;
	if (root->flags == NULL && root->treated_comnd == NULL)
	{
		while (env_iter != NULL)
		{
			printf("%s=%s\n", env_iter->key, env_iter->data);
			env_iter = env_iter->next;
		}
	}
	else
	{
		if (check_pwd_args(root))
		{
			get_pwd = getcwd(NULL, PWD_BUFF);
			printf("%s\n", get_pwd);
			free(get_pwd);
		}
		else
		{
			if (stat(root->treated_comnd->arg, &var_stat) == -1)
			{
				ft_putstr_fd("env: ", STDERR_FILENO);
				ft_putstr_fd(root->treated_comnd->arg, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			}
			else
			{
				ft_putstr_fd("env: ", STDERR_FILENO);
				ft_putstr_fd(root->treated_comnd->arg, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			}
			return (1);
		}
	}
	return (0);
}