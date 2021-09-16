#include "minishell.h"

static void my_exit_free_all(t_vars *vars, t_raw *root)
{
	int		i;

	raw_free_list(root);
	envp_free_list(vars->envp);
	if (vars->paths)
	{
		i = 0;
		while (vars->paths[i])
			free(vars->paths[i++]);
		free(vars->paths);
	}
}


int		my_exit(t_vars *vars, t_raw *root)
{
	int	status;
	int i;
	int	flag;

	i = 0;
	if (!root->treated_comnd)
	{
		printf("exit\n");
		if (root->flags)
			flag = ft_atoi(root->flags + 1);
		my_exit_free_all(vars, root);
		if (root->flags)
			exit(255 - flag + 1);
		exit(0);
	}
	while (ft_isdigit(root->treated_comnd->arg[i]))
	{
		i++;
		status = ft_atoi(root->treated_comnd->arg);
	}
	if (root->treated_comnd->arg[i] == '\0')
	{
		printf("exit\n");
		my_exit_free_all(vars, root);	
		exit(status);
	}
	else
	{
		printf("exit\n");
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(root->treated_comnd->arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument reuired\n", STDERR_FILENO);
	}
	my_exit_free_all(vars, root);
	exit (255);
}