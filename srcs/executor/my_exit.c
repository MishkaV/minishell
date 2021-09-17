/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:34:38 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 16:06:12 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	my_exit_free_all(t_vars *vars, t_raw *root)
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

static void	print_num_arg_reuired(t_raw *root)
{
	printf("exit\n");
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(root->treated_comnd->arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument reuired\n", STDERR_FILENO);
}

static void	my_exit_no_command(t_vars *vars, t_raw *root)
{
	int	flag;

	printf("exit\n");
	if (root->flags)
		flag = ft_atoi(root->flags + 1);
	my_exit_free_all(vars, root);
	if (root->flags)
		exit(255 - flag + 1);
	exit(0);
}

int	my_exit(t_vars *vars, t_raw *root)
{
	int	status;
	int	i;

	i = -1;
	if (root->treated_comnd && trls_get_len(root->treated_comnd) > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!root->treated_comnd)
		my_exit_no_command(vars, root);
	while (ft_isdigit(root->treated_comnd->arg[++i]))
		status = ft_atoi(root->treated_comnd->arg);
	if (root->treated_comnd->arg[i] == '\0')
	{
		printf("exit\n");
		my_exit_free_all(vars, root);
		exit(status);
	}
	else
		print_num_arg_reuired(root);
	my_exit_free_all(vars, root);
	exit (255);
}
