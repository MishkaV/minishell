/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:50:08 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/11 16:01:23 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *curr;

	if (lst)
	{
		while (*lst)
		{
			curr = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = curr;
		}
	}
}
