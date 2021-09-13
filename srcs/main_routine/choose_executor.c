#include "minishell.h"

static int	lexer_before_exec_check(t_raw *root)
{
	int flag;

	flag = 0;
	if (root)
	{
		if (root->command_info.code == -1)
			flag = print_error(ERROR_NOT_FOUND);
		if (!flag && lexer_check_flags(root))
			flag = print_error(ERROR_BAD_FLAG);
	}
	return (flag);
}

void	executor_loop(t_vars *vars, t_raw *root)
{
	if (root)
	{
		while (root)
		{
			if (!lexer_before_exec_check(root))
			{
				choose_executor(vars, root);
				root = root->next;
			}
			else
			{
				root = root->next;
				while (root && root->type == TYPE_PIPE)
					root = root->next;
			}
		}
	}
}


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
		status = my_export(vars, root); //Здесь какая-то дичь, не выводит такой же env

	return (status);
}