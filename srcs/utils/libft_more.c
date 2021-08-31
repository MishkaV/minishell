/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:12:24 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 14:15:33 by jbenjy           ###   ########.fr       */
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

char	*ft_strndup(const char *s1, int n)
{
	char    *str;
	char    *begin;
    int     i;
    
    if (s1)
	{
		
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
	return (0);
}

char	*ft_concat(char *s1, char *s2)
{
	char	*str;
	char	*begin;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);

	begin = str;
	while(*s1)
		*str++ = *s1++;
	while(*s2)
		*str++ = *s2++;
	*str = '\0';
	 
	return (begin);
}

char	*skip_spaces(char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}
