/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:41:35 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/12 11:41:30 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *str;
	char *begin;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	begin = str;
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (begin);
}
