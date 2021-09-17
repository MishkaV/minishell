/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:31:13 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:52:43 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	number_of_words1(char const *s, int c)
{
	unsigned int	i;
	unsigned int	j;

	if (!s[0])
		return (0);
	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			j++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		j++;
	return (j);
}

static	int	len_of_word(char const *s, int c)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static	char	**malloc_free(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	t_split	index;

	if (!s)
		return (NULL);
	index.i = number_of_words1(s, c);
	index.k = 0;
	dst = (char **)malloc(sizeof(char *) * (index.i + 1));
	if (!dst)
		return (NULL);
	while (index.k < index.i)
	{
		index.j = 0;
		while (*s == c)
			s++;
		dst[index.k] = (char *)malloc(sizeof(char) * (len_of_word(s, c) + 1));
		if (!dst[index.k])
			return (malloc_free(dst));
		while (*s != c && *s)
			dst[index.k][index.j++] = *s++;
		dst[index.k++][index.j] = '\0';
	}
	dst[index.k] = NULL;
	return (dst);
}
