/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:02:15 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:53:20 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	lens;

	count = 0;
	while (dst[count] && count < dstsize)
		count++;
	lens = count;
	while (count + 1 < dstsize && src[count - lens])
	{
		dst[count] = src[count - lens];
		count++;
	}
	if (count < dstsize)
		dst[count] = '\0';
	return (ft_strlen(src) + lens);
}
