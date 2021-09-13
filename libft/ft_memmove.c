/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:26:24 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/18 12:55:19 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char	*destn;
	unsigned char	*srcn;

	destn = (unsigned char *)dest;
	srcn = (unsigned char *)src;
	if (!num || destn == src)
		return (destn);
	if (destn < srcn)
	{
		while (num--)
			*destn++ = *srcn++;
	}
	else
	{
		destn = destn + num - 1;
		srcn = srcn + num - 1;
		while (num--)
			*destn-- = *srcn--;
	}
	return (dest);
}
