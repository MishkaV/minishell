/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:47:58 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:50:35 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_not_valid(char *str)
{
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (1);
}

void	my_export_push_node(t_trls *list, t_vars *vars)
{
	char		*key;
	char		*data;

	key = ft_strndup(list->arg, ft_find_chr(list->arg, '='));
	if (!key)
		key = ft_strdup("");
	data = ft_strdup(ft_strchr(list->arg, '=') + 1);
	if (!data)
		data = ft_strdup("");
	if (envp_get_data(vars->envp, key))
	{
		envp_change_data(vars->envp, key, data);
		free(key);
	}
	else
		vars->envp = envp_push_node(vars->envp, key, data);
}

int	my_export_more(t_vars *vars, t_raw *root)
{
	t_trls		*list;
	int			status;

	list = root->treated_comnd;
	status = 0;
	while (list)
	{
		if (list->arg[0] == '=' && !status)
			status = print_not_valid(list->arg);
		else if (list->arg[0] != '=' && ft_strchr(list->arg, '='))
			my_export_push_node(list, vars);
		list = list->next;
	}
	return (status);
}
