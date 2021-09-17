/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:14:00 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:52:08 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t	i;

	i = -1;
	if (!destination && !source)
		return (NULL);
	while (++i < n)
		((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
	return (destination);
}
