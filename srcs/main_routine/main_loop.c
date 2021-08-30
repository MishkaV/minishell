/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:36:47 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/30 13:32:31 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int flag_q;
	int flag_dq;

	flag_q = 0;
	flag_dq = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (!flag_q)
				flag_q = 1;
			else
				flag_q = 0;	
		}
		else if (*str == '\"')
		{
			if (!flag_dq)
				flag_dq = 1;
			else
				flag_dq = 0;	
		}
		str++;
	}
	return (flag_dq || flag_q);
}

int	is_space(char c)
{
	return (c == '\t' || c == '\v' || c == '\r' ||
			c == '\f' || c == '\b' || c == ' ');
}

char	*find_command(char *str, t_raw *commands)
{
	int i;

	i = 0;

	while (str[i] && !is_space(str[i]))
		i++;
	commands->command = ft_strndup(str, i);
	return (str + i + 1);
}

char	*find_flags(char *str, t_raw *command)
{
	int i;
	
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (!ft_strncmp("-n", str + i, 2))
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
	while (str[curr] && str[curr] != '|' && str[curr] != ';')
		curr++;
	commands->argument = ft_strndup(str, curr);
	return (str + curr);
}

// void	init_raw(t_raw *commands)
// {
// 	commands
}

char	**spliting_raw(char *str)
{
	t_raw	*commands;
	t_raw	*last;

	while (*str)
	{
		commands = malloc(sizeof(t_raw));
		commands->argument = 0;
		commands->command = 0;
		commands->flags = 0;
		
		while (*str && is_space(*str))
			str++;
		str = find_command(str, commands);
		str = find_flags(str, commands);
		str = find_arg(str, commands);
		
		printf("%s\n", commands->command);
		printf("%s\n", commands->flags);
		printf("%s\n", commands->argument);
	}
	
	return (0);
}

// void	sig_int(int code)
// {
// 	(void)code;
// 	ft_putstr_fd("\n", 2);
// 	ft_putstr_fd(READLINE_WORDS, 2);
// }


void	main_loop()
{
	char *str;
	
	while (1)
	{
		// signal(SIGINT, &sig_int);
		str = readline(READLINE_WORDS);
		if (check_quotes(str))
			printf("%s%s\n", ERROR_SYNTAX,  "bad number of quotes");
		spliting_raw(str);
		add_history(str);
	}
}