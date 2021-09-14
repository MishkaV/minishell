/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/14 11:03:21 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lexer_get_dollar(t_envp_list *envp, char *str, int dquote)
{
	char	*curr;
	char	*result;
	int		i;

	i = 0;
	if (!str)
		return (0);
	if(str[i] == '$')
		str++;
	if (dquote)
		while (str[i] && !is_space(str[i]) && str[i] != '\"')
			i++;
	else
		while (str[i] && !is_space(str[i]))
			i++;
	curr = ft_strndup(str, i);
	result = ft_strdup(envp_get_data(envp, curr));
	free(curr);
	return (result);
}

char	*lexer_get_text(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && !is_space(str[i]) && str[i] != '\'' && str[i] != '\"')
		i++;
	return (ft_strndup(str, i));
}

char	*lexer_parse_text(t_raw *curr, t_vars *vars, char *str)
{
	char	*result;
	
	if(str[0] == '$')
	{
		if (!ft_strncmp(str, "$?", 2) && (!str[2] || is_space(str[2]) || str[2] == '\'' || str[2] == '\"' ))
			result = lexer_get_text(str);
		else
			result = lexer_get_dollar(vars->envp, str, 0);	
	}
	else
		result = lexer_get_text(str);
	curr->treated_comnd = trls_push_node(curr->treated_comnd, result);
	return (skip_sym(str));
}

char	*lexer_parse_quote(t_raw *curr, char *str)
{
	int i;

	i = 0;
	if (*str == '\'')
		str++;
	while (str[i] && str[i] != '\'')
		i++;
	curr->treated_comnd = trls_push_node(curr->treated_comnd, ft_strndup(str, i));
	return (str + i + 1);
}

static void	lexer_dquote_ret(t_trls *list, t_raw *curr)
{
	char	*result;
	char	*prev;
	t_trls	*begin;
	
	result = 0;
	begin = list;
	while (list)
	{
		prev = result;
		result = ft_concat(result, list->arg);
		if (prev)
			free(prev);
		list = list->next;
	}
	curr->treated_comnd = trls_push_node(curr->treated_comnd, result);
	trls_free_list(begin);
}

char	*lexer_parse_dquote(t_raw *curr, t_vars *vars, char *str)
{
	t_trls	*list;
	char	*path;
	
	list = 0;
	while (*str && *str != '\"')
	{
		if (*str == '$' && ft_isalpha(*(str + 1)))
		{
			path = lexer_get_dollar(vars->envp, str, 1);
			list = trls_push_node(list, path);
			while (*str && !is_space(*str) && *str != '\"')
				str++;
		}
		else if (*str == '\\' && is_dequote(*(str + 1)))
		{
			list = trls_push_node(list, ft_strndup((str + 1), 1));
			str += 2;
		}
		else
			list = trls_push_node(list, ft_strndup(str++, 1));
	}
	lexer_dquote_ret(list, curr);
	return (str + 1);
}

void	lexer_parse_arg(t_raw *curr, t_vars *vars)
{
	char *str;

	str = curr->argument;
	if (str)
	{
		while (*str)
		{
			str = skip_spaces(str);
			if (*str == '\'')
				str = lexer_parse_quote(curr, str);
			else if (*str == '\"')
				str = lexer_parse_dquote(curr, vars, str + 1);
			else if (*str != '\0')
				str = lexer_parse_text(curr, vars, str);
		}
	}
}

void	lexer_analysis(t_raw *root, t_vars *vars)
{
	if (root)
		while (root)
		{
			lexer_check_command(root, vars);
			lexer_parse_arg(root, vars);
			root = root->next;
		}
}