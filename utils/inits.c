/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 20:38:21 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/23 15:15:34 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int  find_len_envp(char **envp)
// {
// 	int count;

// 	count = 0;
// 	while (envp[count])
// 		count++;
// 	return (count);
// }

int init_envp(t_vars *vars, char **envp)
{
	int		i;
	char	*key;
	char	*data;
	i = 0;
	vars->envp = 0;
	
	while (envp[i])
	{
		key = ft_strndup(envp[i], ft_find_chr(envp[i], '='));
		data = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (!key || !data)
			return (0);
		vars->envp = envp_push_node(vars->envp, key, data);
		i++;
	}
	envp[i] = 0;
	return (0);
}