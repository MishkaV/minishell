/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:53:52 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/16 10:53:42 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int my_cd_no_home(void)
{
    ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	return (1);
}

static int my_cd_no_such_file(char *str)
{
    ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
	return (1);
}

int my_cd(t_vars *vars, t_raw *root)
{
    int     status;
    char    *curr_pwd;
    char    *old_pwd;
    char    *to_change;

    status = 0;
    if (root->treated_comnd)
        to_change = root->treated_comnd->arg;
    if (trls_get_len(root->treated_comnd) >= 1)
    {
        if (!to_change)
        {
            if (!envp_get_data(vars->envp, "HOME"))
                return (my_cd_no_home());
            to_change = envp_get_data(vars->envp, "HOME");
                       
        }
        if (chdir(to_change) != -1)
        {
	        curr_pwd = getcwd(NULL, PWD_BUFF);
            if (!curr_pwd)
		        exit(errno);
            old_pwd = envp_get_data(vars->envp, "PWD");
            if (old_pwd)
                envp_change_data(vars->envp, "OLDPWD", ft_strdup(old_pwd));
            envp_change_data(vars->envp, "PWD", curr_pwd);
        }
        else
            return (my_cd_no_such_file(to_change));
    }
    return (status);
}
