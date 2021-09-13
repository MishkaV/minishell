#include "minishell.h"

int		my_exit(t_vars *vars, t_raw *root)
{
	(void)vars;
	int	status;
	int i;
	i = 0;

	while (ft_isdigit(root->treated_comnd->arg[i]))
	{
		i++;
		status = ft_atoi(root->treated_comnd->arg);
	}
	if (root->treated_comnd->arg[i] == '\0')
	{
		printf("exit\n");
		exit(status);
	}
	else
	{
		printf("exit\n");
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(root->treated_comnd->arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument reuired\n", STDERR_FILENO);
	}
	exit (255);
}