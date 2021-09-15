/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/15 23:42:22 by jbenjy           ###   ########.fr       */
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

char	*lexer_get_with_space(char *str, int i)
{
	char *before;
	char *after;

	before = ft_strndup(str, i);
	after = ft_strdup(str + i + 1);
	str = ft_concat(before, after); 
	free(before);
	free(after);
	return (str);
}

char	*lexer_get_text(char *str)
{
	int i;
	int flag;
	char	*curr;

	i = 0;
	flag = 0;
	if (!str)
		return (0);
	while (str[i] && !is_space(str[i]) && str[i] != '\'' && str[i] != '\"')
	{
		if (str[i] == '\\' && str[i + 1] == ' ')
		{
			str = lexer_get_with_space(str, i);
			i++;
		}
		i++;
	}
	curr = ft_strndup(str, i);
	if (flag)
		free(str);
	return (curr);
}

char	*lexer_parse_text(t_raw *curr, t_vars *vars, char *str)
{
	char	*result;
	
	if(str[0] == '$')
	{
		if (!ft_strncmp(str, "$?", 2) && (!str[2] || is_space(str[2]) || str[2] == '\'' || str[2] == '\"' ))
			result = ft_itoa(vars->status);
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

void	lexer_parse_redirect(t_raw *root, t_vars *vars)
{
	t_redirect	*list;
	char		*path;
	char		*before;
	char		*after;
	int			i;

	list = root->redirects; 
	if (list)
	{
		while (list)
		{
			if (list->file && list->quote != 1)
			{
				while (ft_strchr(list->file, '$'))
				{	
					path = lexer_get_dollar(vars->envp, ft_strchr(list->file, '$'), 0);
					before = ft_strndup(list->file, ft_strchr(list->file, '$') - list->file);
					i = 0;
					while (list->file[i] && list->file[i] != '$')
						i++;
					while (list->file[i] && !is_space(list->file[i]))
						i++;
					after = ft_strdup(list->file + i);
					free(list->file);
					
					list->file = ft_concat(before, path);
					free(path);
					free(before);
					
					before = list->file;
					list->file = ft_concat(list->file, after);
					free(before);
					free(after);
				}
			}
			list = list->next;
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
			lexer_parse_redirect(root, vars);
			root = root->next;
		}
}