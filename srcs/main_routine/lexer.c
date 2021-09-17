/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 14:44:27 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	lexer_parse_redir_skip(t_redirect *list)
{
	int	i;

	i = 0;
	while (list->file[i] && list->file[i] != '$')
		i++;
	while (list->file[i] && !is_space(list->file[i]))
		i++;
	return (i);
}

static void	lexer_parse_redir_free(t_redirect *list, t_vars *vars)
{
	char		*path;
	char		*before;
	char		*after;
	int			i;

	while (ft_strchr(list->file, '$'))
	{	
		path = lexer_get_dollar(vars->envp,
				ft_strchr(list->file, '$'), 0);
		before = ft_strndup(list->file,
				ft_strchr(list->file, '$') - list->file);
		i = lexer_parse_redir_skip(list);
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

void	lexer_parse_redirect(t_raw *root, t_vars *vars)
{
	t_redirect	*list;

	list = root->redirects;
	if (list)
	{
		while (list)
		{
			if (list->file && list->quote != 1)
				lexer_parse_redir_free(list, vars);
			list = list->next;
		}
	}
}
