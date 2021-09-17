/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:55:36 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:55:49 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(void)
{
	char	*str_pwd;

	str_pwd = getcwd(NULL, PWD_BUFF);
	if (str_pwd == NULL)
		exit(errno);
	printf("%s\n", str_pwd);
	free(str_pwd);
	return (0);
}
