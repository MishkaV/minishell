#include "minishell.h"

int		my_unset(t_vars *vars, t_raw *root)
{
	t_trls *list;
	int		flag;
	
	list = root->treated_comnd;
	if (ft_strncmp(root->command, "unset", 6) == 0 && root->flags == NULL && root->treated_comnd == NULL)
	{
		ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (1);
	}
	flag = 0;
	while (list)
	{
		if (ft_strchr(list->arg, '=') && !flag)
		{
			ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(list->arg, STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			flag = 1;
		}
		vars->envp = envp_pop_by_key(vars->envp, list->arg);
		list = list->next;
	}
	return (0);
}
