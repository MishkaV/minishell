/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:36:47 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 14:17:17 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command(char *str, t_raw *commands)
{
	int i;

	if (str)
	{
		i = 0;
		while (str[i] && !is_space(str[i]))
			i++;
		commands->command = ft_strndup(str, i);
		return (str + i + 1);	
	}
	return (0);	
}

char	*find_flags(char *str, t_raw *command)
{
	int i;

	i = 0;
	if (str)
	{
		str = skip_spaces(str);
		if (!ft_strncmp("-n", str, 2))
		{
			command->flags = ft_strndup("-n", 2);
			i += 3;
		}
		return (str + i);	
	}
		return (0);
}

char	*find_arg(char *str, t_raw *commands)
{
	int	curr;

	curr = 0;
	if (str)
	{
		str = skip_spaces(str);
		while (str[curr] && str[curr] != '|' && str[curr] != ';' && str[curr] != '<' && str[curr] != '>')
			curr++;
		commands->argument = ft_strndup(str, curr);
		return (str + curr);	
	}
	return (0);
}

char	*find_pipe(char *str, t_raw *command)
{
	int i;
	int type;

	i = 0;
	if (*str && (*str == '<' || *str == '>'))
	{
		type = *str == '<' ? 1 : 0;
		if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
		{
			command->type_redirect = 2;
			str += 1;
		}
		else
			command->type_redirect = 1;
		str += 1;
		
		while (*str && *str != '|' && *str != ';' && is_space(*str))
			str++;
		while (str[i] && str[i] != '|' && str[i] != ';')
			i++;
		
		if (type == 1)
			command->in = ft_strndup(str, i);
		else
			command->out = ft_strndup(str, i);

	}

	return (str + i + 1);
}

t_raw	*spliting_raw(char *str)
{
	t_raw	*root;
	t_raw	*curr;
	
	root = 0;
	while (*str)
	{
		curr = raw_new_node();
		
		str = skip_spaces(str);
		str = find_command(str, curr);
		str = find_flags(str, curr);
		str = find_arg(str, curr);
		str = find_pipe(str, curr);
		root = raw_push(root, curr);
		if (*str)
			break;
	}
	
	raw_print_list(root);
	raw_free_list(root);
	return (0);
}

void	main_loop()
{
	char *str;
	
	while (1)
	{
		// signal(SIGINT, &signal_int);
		str = readline(READLINE_WORDS);
		if (check_quotes(str))
			printf("%s%s\n", ERROR_SYNTAX,  "bad number of quotes");
		spliting_raw(str);
		add_history(str);
	}
}