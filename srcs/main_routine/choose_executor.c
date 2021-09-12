#include "minishell.h"

int		choose_executor(t_vars *vars, t_raw *root)
{
	int status;

	(void)vars;
	status = 0;
	if (ft_strncmp(root->command, "echo", 5) == 0)
		status = my_echo(root);
	else if (ft_strncmp(root->command, "pwd", 4) == 0)
		status = my_pwd(root);
	else if (ft_strncmp(root->command, "env", 4) == 0)
		status = my_env(*vars, root);
	else if (ft_strncmp(root->command, "unset", 6) == 0)
		status = my_unset(vars, root);
	else if (ft_strncmp(root->command, "export", 7) == 0)
		status = my_export(vars, root);

	return (status);
}