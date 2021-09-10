/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:26:44 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/03 19:23:27 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_vars vars;
	
	init_envp(&vars, envp);
	main_loop(&vars);
	
	envp_free_list(vars.envp);
	if (vars.paths)
		free(vars.paths); 
	return (0);
}
