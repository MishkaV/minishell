/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:26:27 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/01 12:53:48 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	signal_int(int code)
{
	(void)code;

	ft_putstr_fd("\n", 2);
	ft_putstr_fd(READLINE_WORDS, 2);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	// ft_putstr_fd("\b", 2);
	// ft_putstr_fd(READLINE_WORDS, 2);
}

void	signal_quit(int code)
{
	(void)code;
	
	// ft_putstr_fd("\b\b \b\b", 2);
}