/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_nondefault.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:39:11 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:16:32 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_argv(t_raw *root)
{
	int		len;
	char	**argv;
	int		i;
	t_trls	*list;
	
	
	len = trls_get_len(root->treated_comnd);
	argv = malloc(sizeof(char *) * (len + 2));
	if (!argv)
		return (0);
		
	argv[0] = ft_strdup(root->command);
	list = root->treated_comnd;
	i = 1;
	
	while (list)
	{
		argv[i++] = ft_strdup(list->arg);
		list = list->next;
	}
	argv[i] = 0;
	return (argv);
}

static void	free_list(char **list)
{
	int i;
	
	i = 0;
	if (list)
	{
		while (list[i])
		{
			if (list[i])
				free(list[i]);
			i++;
		}
		free(list);	
	}
}

static char *make_path(t_vars *vars, t_raw *root)
{
	char	*path;
	char	*buff;

	if (check_is_full_path_command(root->command))
		return(ft_strdup(root->command));
	if (root->command_info.code == COMMAND_PWD)
	{
		if (envp_get_data(vars->envp, "PWD"))
			buff = ft_concat(envp_get_data(vars->envp, "PWD"), "/");
		else if (envp_get_data(vars->envp, "HOME"))
			buff = ft_concat(envp_get_data(vars->envp, "HOME"), "/");
		else
			return (0);
		path = ft_concat(buff, root->command + 2);	
	}
	else
	{
		buff = ft_concat(vars->paths[root->command_info.code], "/");
		path = ft_concat(buff, root->command);
	}
	free(buff);
	return (path);
}

int	is_minishell(t_raw *root)
{
	if (!ft_strcmp(root->command, "./minishell"))
		return (1);
	return (0);	
}

int my_nondefault(t_vars *vars, t_raw *root)
{
	char	**envp;
	char	**argv;
	int		pid;
	int		status;
	char	*path;

	if (is_minishell(root))	
		envp = envp_to_char(vars->envp);
	else
		envp = envp_to_char(vars->envp);
	argv = make_argv(root);
	path = make_path(vars, root);
	pid = fork();
	status = 0;
	if (pid == -1)
		return (1);
	if (!pid)
		execve(path, argv, envp);
	waitpid(pid , &status, 0);
	free(path);
	free_list(envp);
	free_list(argv);
	return (status);
}
