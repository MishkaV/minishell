/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:12:24 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/23 14:25:08 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}

int		ft_find_chr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int ft_min(int n1, int n2)
{
    if (n1 < n2)
        return (n1);
    return (n2);
}

int ft_max(int n1, int n2)
{
    if (n1 < n2)
        return (n2);
    return (n1);
}

char	*ft_strndup(const char *s1, int n)
{
	char    *str;
	char    *begin;
    int     i;
    
    
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	begin = str;
    i = 0; 
	if (!str || n < 0)
		return (NULL);
	while (*s1 && i != n)
    {
        *str++ = *s1++;
	    i++;
    }
	*str = '\0';
	return (begin);
}
