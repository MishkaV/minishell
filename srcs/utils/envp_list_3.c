/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:48:04 by lsinistr          #+#    #+#             */
/*   Updated: 2021/09/17 12:48:32 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**envp_to_char(t_envp_list *root)
{
	char	**list;
	int		len;
	int		i;
	char	*buff;

	if (!root)
		return (0);
	len = envp_get_len(root);
	if (len)
	{
		list = malloc(sizeof(char *) * (len + 1));
		if (!list)
			return (0);
		i = 0;
		while (root)
		{
			buff = ft_concat(root->key, "=");
			list[i++] = ft_concat(buff, root->data);
			free(buff);
			root = root->next;
		}
		list[i] = 0;
		return (list);
	}
	return (0);
}
