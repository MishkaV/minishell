/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:31:39 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:51:02 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		*((unsigned char *)destination) = *((unsigned char *)source);
		if (*((unsigned char *)destination) == (unsigned char)c)
			return (destination + 1);
		destination++;
		source++;
	}
	return (0);
}
