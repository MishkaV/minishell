/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:26:27 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/10 13:32:19 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	signal_int(int code)
{
	(void)code;
	
	printf("\n");
	rl_on_new_line();	
	rl_replace_line("", 0);	
	rl_redisplay();	
}


void	signal_quit(int code)
{
	(void)code;

	// printf("\b ");
	// rl_redisplay();	
	// printf("");
}