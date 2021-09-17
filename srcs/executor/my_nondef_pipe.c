/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_nondef_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:39:11 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:53:46 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_argv_pipe(t_raw *root)
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

static void	free_list_pipe(char **list)
{
	int	i;

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

static char	*make_path_pipe(t_vars *vars, t_raw *root)
{
	char	*path;
	char	*buff;

	if (check_is_full_path_command(root->command))
		return (ft_strdup(root->command));
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

static int	is_minishell_pipe(t_raw *root)
{
	if (!ft_strcmp(root->command, "./minishell"))
		return (1);
	return (0);
}

int	my_nondefault_pipe(t_vars *vars, t_raw *root)
{
	char	**envp;
	char	**argv;
	int		status;
	char	*path;

	if (is_minishell_pipe(root))
		envp = envp_to_char(vars->envp);
	else
		envp = envp_to_char(vars->envp);
	argv = make_argv_pipe(root);
	path = make_path_pipe(vars, root);
	status = 0;
	execve(path, argv, envp);
	free(path);
	free_list_pipe(envp);
	free_list_pipe(argv);
	return (status);
}
