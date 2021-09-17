/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:39:32 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 14:44:39 by jbenjy           ###   ########.fr       */
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
	if (str[i] == '$')
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
	char	*before;
	char	*after;

	before = ft_strndup(str, i);
	after = ft_strdup(str + i + 1);
	str = ft_concat(before, after);
	free(before);
	free(after);
	return (str);
}

char	*lexer_get_text(char *str)
{
	int		i;
	int		flag;
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

	if (str[0] == '$')
	{
		if (!ft_strncmp(str, "$?", 2) && (!str[2] || is_space(str[2])
				|| str[2] == '\'' || str[2] == '\"' ))
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
	int	i;

	i = 0;
	if (*str == '\'')
		str++;
	while (str[i] && str[i] != '\'')
		i++;
	curr->treated_comnd = trls_push_node(curr->treated_comnd,
			ft_strndup(str, i));
	return (str + i + 1);
}
