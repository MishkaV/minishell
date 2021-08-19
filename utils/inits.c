/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 20:38:21 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/19 21:16:37 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  find_len_envp(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int init_envp(s_vars *vars, char **envp)
{
	int	len;
	int	i;

	len = find_len_envp(envp);
	i = 0;
	
	vars->envp = malloc(sizeof(char *) * (len + 1));
	if (!vars->envp)
		return (1);
	
	while (envp[i])
	{
		vars->envp[i] = ft_strdup(envp[i]);
		if (!vars->envp[i])
			return (1);
		i++;
	}
	envp[i] = 0;
	return (0);
}