/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 21:16:07 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/19 21:17:52 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_all(s_vars *vars)
{
    int i;

    i = 0;
    while (vars->envp[i])
        free(vars->envp[i++]);
    free(vars->envp);   
}