/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_more_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:37:35 by lsinistr          #+#    #+#             */
/*   Updated: 2021/09/17 12:38:12 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}

char	*skip_sym(char *str)
{
	while (*str && !is_space(*str) && *str != '\'' && *str != '\"')
		str++;
	return (str);
}

char	*ft_tolower_str(char *str)
{
	char	*to_return;
	int		i;

	i = 0;
	to_return = 0;
	if (str)
	{
		to_return = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!to_return)
			return (0);
		while (str[i])
		{
			to_return[i] = ft_tolower(str[i]);
			i++;
		}
		to_return[i] = '\0';
	}
	return (to_return);
}
