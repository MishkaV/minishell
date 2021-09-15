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
				pipes_loop(vars, root);
				root = root->next;
				while (root && root->type == TYPE_PIPE)
					root = root->next;
			}
			else
			{
				vars->status = 1;
				root = root->next;
				while (root && root->type == TYPE_PIPE)
					root = root->next;
			}
		}
	}
}

// Доделать с кавычками парсер ls > "file kek"
int		choose_executor(t_vars *vars, t_raw *root)
{
	int status;

	status = 0;

	if (ft_strcmp(root->command, "echo") == 0)
		status = my_echo(root);
	else if (ft_strcmp(root->command, "pwd") == 0)
		status = my_pwd(root);
	else if (ft_strcmp(root->command, "env") == 0)
		status = my_env(*vars, root); 
	else if (ft_strcmp(root->command, "unset") == 0)
		status = my_unset(vars, root);
	else if (ft_strcmp(root->command, "export") == 0)
		status = my_export(vars, root);
	else if (ft_strcmp(root->command, "cd") == 0)
		status = my_cd(vars, root);
	else if (ft_strcmp(root->command, "exit") == 0)
		status = my_exit(vars, root);
	else if (root->command_info.code != COMMAND_EMPTY)
		status = my_nondefault(vars, root);

	return (status);
}
