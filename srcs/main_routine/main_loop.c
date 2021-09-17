/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:36:47 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 14:49:53 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_raw	*spliting_raw(char *str)
{
	t_raw	*root;
	t_raw	*curr;
	int		check_type;

	root = 0;
	check_type = TYPE_COMMAND;
	while (*str)
	{
		curr = raw_new_node();
		curr->type = check_type;
		check_type = TYPE_COMMAND;
		str = skip_spaces(str);
		str = find_command(str, curr);
		str = find_flags(str, curr);
		str = find_arg(str, curr);
		str = find_pipe(str, curr, &check_type);
		root = raw_push(root, curr);
	}
	return (root);
}

static void	main_loop_more(char *str, t_raw *root, t_vars *vars)
{
	if (check_quotes(str))
		print_error(ERROR_QUOTES);
	else
	{
		root = spliting_raw(str);
		lexer_analysis(root, vars);
		executor_loop(vars, root);
		raw_free_list(root);
	}
}

void	main_loop(t_vars *vars)
{
	char	*str;
	t_raw	*root;

	root = 0;
	while (1)
	{
		signal(SIGINT, &signal_int);
		signal(SIGQUIT, SIG_IGN);
		str = readline(READLINE_WORDS);
		if (str)
			main_loop_more(str, root, vars);
		else
		{
			printf("\b\b%s\n", GOOD_BYE);
			break ;
		}
		add_history(str);
		free(str);
		unlink("./temporary/temp");
	}
}
