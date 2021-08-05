/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:10:17 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/11 15:22:33 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	i = 0;
	if (!*needle)
		return ((char*)haystack);
	if (!*haystack)
		return (0);
	while (i + ft_strlen(needle) <= len && *haystack)
	{
		if (!ft_memcmp(haystack, needle, ft_strlen(needle)))
			return ((char*)haystack);
		haystack++;
		i++;
	}
	return (0);
}
