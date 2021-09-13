/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:11:00 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/18 12:54:37 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*tail;
	char	*str;
	int		len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char*)s1);
	start = (char*)s1;
	tail = (char*)s1 + ft_strlen(s1);
	while (ft_strchr(set, *start) && *start)
		start++;
	while (ft_strchr(set, *(tail - 1)) && start != tail)
		tail--;
	len = tail - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, start, (size_t)len + 1);
	return (str);
}
