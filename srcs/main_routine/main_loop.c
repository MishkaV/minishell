/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:36:47 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 16:15:55 by jbenjy           ###   ########.fr       */
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

char	*find_pipe(char *str, t_raw *command)
{
	int i;
	int type;

	// if (*str && (*str == '<' || *str == '>'))
	// {
	// 	type = *str == '<' ? 1 : 0;
	// 	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
	// 	{
	// 		command->type_redirect = 2;
	// 		str += 1;
	// 	}
	// 	else
	// 		command->type_redirect = 1;
	// 	str += 1;
		
	// 	while (*str && *str != '|' && *str != ';' && is_space(*str))
	// 		str++;
	// 	while (str[i] && str[i] != '|' && str[i] != ';')
	// 		i++;
		
	// 	if (type == 1)
	// 		command->in = ft_strndup(str, i);
	// 	else
	// 		command->out = ft_strndup(str, i);

	// }
	// return (str + i);
	// while (*str && str)
	while (*str && is_special(*str))
	{
		i = 0;
		if (*str == '|' || *str == ';')
			return (str + 1);
		
		type = *str == '<' ? 1 : 0; // 1 == <, 0 == >
		if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
		{
			command->type_redirect = 2;
			str += 1;
		}
		else
			command->type_redirect = 1;
		str += 1;
		
		str = skip_spaces(str);
		while (str[i] && !is_special(str[i]))
			i++;
		if (type == 1)
			command->in = ft_strndup(str, i);
		else
			command->out = ft_strndup(str, i);
		str += i;
	}
	return (str);
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
		if (!*str)
			break;
	}
	
	raw_print_list(root);
	raw_free_list(root);
	return (root);
}

void	main_loop()
{
	char *str;
	// t_raw *root;
	
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