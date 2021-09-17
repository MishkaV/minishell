/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_exec_more.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:15:48 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 13:17:47 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_executor(t_vars *vars, t_raw *root)
{
	int	status;

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

int	choose_executor_pipe(t_vars *vars, t_raw *root)
{
	int	status;

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
		status = my_nondefault_pipe(vars, root);
	return (status);
}
