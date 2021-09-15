/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:26:27 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/15 13:41:18 by jbenjy           ###   ########.fr       */
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
