/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:55:05 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/15 18:13:07 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!ft_strncmp("-", str, 1))
	{
		while (str[i] && !is_space(str[i]) && !is_special(str[i]))
			i++;
		command->flags = ft_strndup(str, i);
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

static char *find_argv_more(char *str, t_raw *command)
{
	int			i;
	char		*buff1;
	char		*buff2;
	char		*new_arg;

	i = 0;
	if (!is_special(str[i]))
	{
		while (str[i] && !is_special(str[i]))
			i++;
		buff1 = command->argument;
		buff2 = ft_concat(command->argument, " ");
		new_arg = ft_strndup(str, i);
		command->argument = ft_concat(buff2, new_arg);
		free(buff1);
		free(buff2);
		free(new_arg);
	}
	return (str + i);
}

// static char *get_envp_dollar(char *str, char c, t_vars *vars)
// {
// 	char *before;
// 	char *path;
// 	char *after;
// 	char *result;
// 	int i;

// 	i = 0;
// 	before = ft_strndup(str, ft_strchr(str, '$') - str);
// 	path = ft_strchr(str, '$') + 1;
// 	while (path[i] & !is_space(path[i]) && path[i] != c)
// 		i++;
// 	after = ft_strndup(path, i - 1);
// 	path = envp_get_data(vars->envp, after);
// 	free(after);
// 	after = ft_strdup(path + i);
// 	result = ft_concat(before, path);
	
// 	free(before);
// 	before = result;

// 	result = ft_concat(result, after);
// 	free(before);
// 	free(after);
// 	free(str);
// 	return (result);
// }

static char  *find_quotes(char *str, t_redirect *curr_rct)
{
	int		i;
	char	c;

	i = 0;
	if (*str == '\'')
	{
		c = '\'';
		curr_rct->quote = 1;
	}
	else
	{
		c = '\"';
		curr_rct->quote = 2;
	}
	str++;
	while (str[i] && str[i] != c)
		i++;
	curr_rct->file = ft_strndup(str, i);
	if (!str[i])
		return (str + i);
	else
		return (str + i + 1);
}

char	*find_pipe(char *str, t_raw *command, int *check_type)
{
	int			i;
	t_redirect	*curr_rct;

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
		if (*str == '\'' || *str == '\"')
			str = find_quotes(str, curr_rct);
		else
		{
			while (str[i] && !is_space(str[i]) && !is_special(str[i]))
				i++;
			curr_rct->file = ft_strndup(str, i);
		}
		command->redirects = rct_push(command->redirects, curr_rct);
		while (str[i] && is_space(str[i]))
				i++;
		str += i;
		str = find_argv_more(str, command);
	}
	return (str);
}
