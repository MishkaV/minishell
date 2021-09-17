/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:55:58 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:56:15 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_unset(t_vars *vars, t_raw *root)
{
	t_trls	*list;
	int		flag;

	list = root->treated_comnd;
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
