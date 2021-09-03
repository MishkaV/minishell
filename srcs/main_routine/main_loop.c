/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:36:47 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/03 12:50:46 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	return (c == '|' || c == ';' || c == '<' || c == '>');
}

char	*find_command(char *str, t_raw *commands)
{
	int i;

	i = 0;
	while (str[i] && !is_space(str[i]) && !is_special(str[i]))
		i++;
	commands->command = ft_strndup(str, i);
	return (str + i);
}

char	*find_flags(char *str, t_raw *command)
{
	int i;

	i = 0;
	str = skip_spaces(str);
	if (!ft_strncmp("-n", str, 2))
	{
		command->flags = ft_strndup("-n", 2);
		i += 3;
	}
	return (str + i);
}

char	*find_arg(char *str, t_raw *commands)
{
	int	curr;

	curr = 0;
	str = skip_spaces(str);
	while (str[curr] && !is_special(str[curr]))
		curr++;
	commands->argument = ft_strndup(str, curr);
	return (str + curr);
}

char	*check_rct(t_redirect *curr_rct, char *str)
{
	if (*str == '<')
	{
		if (!ft_strncmp(str, "<<", 2))
			curr_rct->type = DOUBLE_IN;
		else
			curr_rct->type = SINGLE_IN;
	}
	else
	{
		if (!ft_strncmp(str, ">>", 2))
			curr_rct->type = DOUBLE_OUT;
		else
			curr_rct->type = SINGLE_OUT;
	}
	while (*str && (*str == '<' || *str == '>'))
		str++;
	return (str);
}

char	*find_pipe(char *str, t_raw *command, int *check_type)
{
	int i;
	t_redirect *curr_rct;

	while (*str && is_special(*str))
	{
		i = 0;
		if (*str == '|' || *str == ';')
		{
			if (*str == '|')
				*check_type = TYPE_PIPE;
			return (str + 1);
		}
			
		curr_rct = rct_new_node();
		str = check_rct(curr_rct, str);
		str = skip_spaces(str);
		while (str[i] && !is_special(str[i]))
			i++;
		
		curr_rct->file = ft_strndup(str, i);
		command->redirects = rct_push(command->redirects, curr_rct);
		str += i;
	}
	return (str);
}



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
	raw_print_list(root);
	raw_free_list(root);
	return (root);
}

void	main_loop()
{
	char *str;
	
	while (1)
	{
		// signal(SIGINT, &signal_int);
		str = readline(READLINE_WORDS);
		if (str)
		{
			if (check_quotes(str))
				printf("%s%s\n", ERROR_SYNTAX,  "bad number of quotes");
			spliting_raw(str);
		}
		else
		{
			printf("\b\b%s\n", GOOD_BYE);
			break ;	
		}
		add_history(str);
	}
}