/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:22:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:24:05 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_with_flag(t_trls *list)
{
	while (list != NULL)
	{
		if (list->arg)
			printf("%s", list->arg);
		if (list->next != NULL)
			printf(" ");
		list = list->next;
	}
	printf("%%\n");
}

int	my_echo(t_raw *root)
{
	t_trls	*list;

	list = root->treated_comnd;
	if (root->flags == NULL && list == NULL)
	{
		printf("\n");
		return (0);
	}
	if (root->flags != NULL && ft_strncmp(root->flags, "-n", 3) == 0)
		print_with_flag(list);
	else
	{
		while (list != NULL)
		{
			if (list->arg)
				printf("%s", list->arg);
			if (list->next != NULL)
				printf(" ");
			list = list->next;
		}
		printf("\n");
	}
	return (0);
}
