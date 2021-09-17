/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:04:23 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 16:34:09 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_before_exec_check(t_raw *root, t_vars *vars)
{
	int	flag;

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
		if (!flag && lexer_check_flags(root)
			&& root->command_info.code != COMMAND_EXIT)
			flag = print_error(ERROR_BAD_FLAG);
	}
	return (flag);
}

static void	executor_more(t_raw *root, t_vars *vars)
{
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

void	executor_loop(t_vars *vars, t_raw *root)
{
	int		old_in;
	int		old_out;
	t_raw	*curr;

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
		executor_more(root, vars);
	}
	dup2(old_in, STDIN_FILENO);
	close(old_in);
	dup2(old_out, STDOUT_FILENO);
	close(old_out);
}
