#include "minishell.h"

static	int	check_pwd_args(char **str_mass)
{
	return (((ft_strncmp(str_mass[1], "pwd", 4) == 0 || ft_strncmp(str_mass[1], "PWD", 4) == 0) && str_mass[2] == NULL)
		|| ((ft_strncmp(str_mass[1], "pwd", 4) == 0 || ft_strncmp(str_mass[1], "PWD", 4) == 0)
		&& ft_strncmp(str_mass[2], "-L", 3) == 0 && str_mass[3] == NULL)
		|| ((ft_strncmp(str_mass[1], "pwd", 4) == 0 || ft_strncmp(str_mass[1], "PWD", 4) == 0)
		&& ft_strncmp(str_mass[2], "-P", 3) == 0 && str_mass[3] == NULL));
}

int		my_env(t_vars vars, char **str_mass)
{
	t_envp_list	*env;
	t_envp_list *env_iter;
	char		*get_pwd;
	struct stat var_stat;

	env = vars.envp;
	env_iter = env;
	if (str_mass[1] == NULL)
	{
		while (env_iter != NULL)
		{
			printf("%s=%s\n", env_iter->key, env_iter->data);
			env_iter = env_iter->next;
		}
	}
	else
	{
		if (check_pwd_args(str_mass))
		{
			get_pwd = getcwd(NULL, PWD_BUFF);
			printf("%s\n", get_pwd);
			free(get_pwd);
		}
		else
		{
			if (stat(str_mass[1], &var_stat) == -1)
			{
				ft_putstr_fd("env: ", STDERR_FILENO);
				ft_putstr_fd(str_mass[1], STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			}
			else
			{
				ft_putstr_fd("env: ", STDERR_FILENO);
				ft_putstr_fd(str_mass[1], STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			}
			return (1);
		}
	}
	return (0);
}