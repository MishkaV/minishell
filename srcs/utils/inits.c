/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 20:38:21 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:47:01 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_path(t_vars *vars)
{
	char	*str;

	str = envp_get_data(vars->envp, "PATH");
	if (str)
		vars->paths = ft_split(str, ':');
}

int	init_envp(t_vars *vars, char **envp)
{
	int		i;
	char	*key;
	char	*data;

	i = -1;
	vars->envp = 0;
	while (envp[++i])
	{
		key = ft_strndup(envp[i], ft_find_chr(envp[i], '='));
		if (!key)
			return (0);
		if (!ft_strcmp(key, "SHLVL"))
			data = ft_itoa(ft_atoi(ft_strchr(envp[i], '=') + 1) + 1);
		else
			data = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (!data)
		{
			free(key);
			return (0);
		}
		vars->envp = envp_push_node(vars->envp, key, data);
	}
	envp[i] = 0;
	init_path(vars);
	return (0);
}
