/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:26:27 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 13:44:40 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	signal_int(int code)
{
	(void)code;
	// ft_putstr_fd("\b", 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd(READLINE_WORDS, 2);
}