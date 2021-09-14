/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_nondefault.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:39:11 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/14 11:33:49 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_nondefault(t_vars *vars, t_raw *root)
{
	char	**envp;
	int		i;
	int		pid;
	// char	*path;
	// char	*buff;
	
	envp = envp_to_char(vars->envp); // Почистить?
	pid = fork();
	if (pid == -1)
		return (1);
	if (!pid)
	{
		// if (root->command_info.code == COMMAND_PWD)
		// 	path = ft_strdup(root->command);
		// else
		// {
		// 	buff = ft_concat(vars->paths[root->command_info.code], "/");
		// 	path = ft_concat(buff, root->command);
		// 	free(buff);
		// }
		// puts(path);
		// puts("CHILD");
		// execve(path, 0, 0);
		// free(path);
		(void)root;
		char **check;
		check = malloc(sizeof(char *) * 1);
		check[0] = ft_strdup("\0");
		execve("/bin/ls", check, 0);
		exit(0);
	}
	puts("PARENT");
	if (envp)
	{
		i = -1;
		while (envp[++i])
			if (envp[i])
				free(envp[i]);
		free(envp);	
	}
	return (0);
}