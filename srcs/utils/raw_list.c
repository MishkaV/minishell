/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:41:32 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:30:20 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_raw	*raw_get_last(t_raw *root)
{
	if (!root)
		return (0);
	while (root->next)
		root = root->next;
	return (root); 
}

t_raw	*raw_new_node(void)
{
	t_raw *curr;

	curr = malloc(sizeof(t_raw));
	if (!curr)
		return (0);
	curr->command = 0;
	curr->flags = 0;
	curr->argument = 0;
	curr->redirects = 0;
	curr->type = 0;
	curr->next = 0;
	curr->command_info.is_default = COMMAND_DEFAULT;
	curr->command_info.code = -1;
	curr->treated_comnd = 0;
	return (curr);
}

t_raw	*raw_push(t_raw *root, t_raw *new_node)
{
	t_raw *to_return;

	to_return = root;
	if (!root)
		return (new_node);
	root = raw_get_last(root);
	root->next = new_node;
	return (to_return);
}

void	raw_print_list(t_raw *root)
{
	while (root)
	{
		printf("Command: |%s|\n", root->command);
		printf("Flag: |%s|\n", root->flags);
		printf("Argument: |%s|\n", root->argument);
		printf("Type: |%d|\n", root->type);
		printf("Redirects:\n");
		rct_print(root->redirects);
		printf("Command info:\n");
		printf("Default: %d\n", root->command_info.is_default);
		printf("Code: %d\n", root->command_info.code);
		printf("After treading:\n");
		trls_print_list(root->treated_comnd);
		printf("\n");
		root = root->next;
	}
}