/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:26:44 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 14:50:50 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		i;

	(void)argc;
	(void)argv;
	vars.status = 0;
	init_envp(&vars, envp);
	main_loop(&vars);
	envp_free_list(vars.envp);
	if (vars.paths)
	{
		i = 0;
		while (vars.paths[i])
			free(vars.paths[i++]);
		free(vars.paths);
	}
	return (0);
}
