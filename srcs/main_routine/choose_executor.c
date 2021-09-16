#include "minishell.h"

static int	lexer_before_exec_check(t_raw *root, t_vars *vars)
{
	int flag;

	flag = 0;
	if (root)
	{
		if (root->command_info.code == -1)
		{
			if (!ft_strcmp(root->command, "$?"))
			{
				ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
				ft_putnbr_fd(vars->status, 2);
				ft_putstr_fd(": command not found", STDERR_FILENO);
				ft_putstr_fd("\n", STDERR_FILENO);
				flag = 1;
			}
			else
				flag = print_error(ERROR_NOT_FOUND);
		
		}
		if (!flag && lexer_check_flags(root) && root->command_info.code != COMMAND_EXIT)
			flag = print_error(ERROR_BAD_FLAG);
	}
	return (flag);
}

void	executor_loop(t_vars *vars, t_raw *root)
{
	int old_in;
	int old_out;
	t_raw *curr;

	signal(SIGINT, &signal_int_child);
	signal(SIGQUIT, &signal_exit_child);
	old_in = dup(STDIN_FILENO);
	old_out = dup(STDOUT_FILENO);

	if (root)
	{
		curr = root;
		while (curr)
		{
			redirect_exec(curr, &old_out, &old_in);
			curr = curr->next;
		}

		while (root)
		{
			if (!lexer_before_exec_check(root, vars))
			{
				vars->status = pipes_loop(vars, root);
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
	dup2(old_in, STDIN_FILENO);
	close(old_in);
	dup2(old_out, STDOUT_FILENO);
	close(old_out);
}

int		choose_executor(t_vars *vars, t_raw *root)
{
	int status;
	status = 0;
	if (ft_strcmp(root->command, "echo") == 0)
		status = my_echo(root);
	else if (ft_strcmp(root->command, "pwd") == 0)
		status = my_pwd();
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
