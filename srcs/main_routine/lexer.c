/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/09 19:27:58 by jbenjy           ###   ########.fr       */
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
	while (str[i] && !is_space(str[i]))
		i++;
	return (ft_strndup(str, i));
}


char	*lexer_parse_text(t_raw *curr, t_vars *vars, char *str)
{
	char	*result;
	
	if(str[0] == '$')
		result = lexer_get_dollar(vars->envp, str, 0);
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

char	*lexer_parse_dquote(t_raw *curr, t_vars *vars, char *str)
{
	int		i;
	char	*result;
	char	*str1;
	char	*str2;
	char	*path;
	
	
	i = 0;
	result = 0;
	if (*str == '\"')
		str++;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			path = lexer_get_dollar(vars->envp, str + i, 1);
			if (path)
			{
				result = ft_concat(result,  path);
				free(path);
			}
			while (str[i] && !is_space(str[i]) && str[i] != '\"')
				i++;
		}
		// else if (str[i] == '\\')
		// {
			
		// }
		else
			i++;
	}
	str1 = result;
	str2 = ft_strndup(str, i);
	result = ft_concat(str1, str2);
	free(str1);
	free(str2);
	curr->treated_comnd = trls_push_node(curr->treated_comnd, result);
	return (str + i + 1);
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
				str = lexer_parse_dquote(curr, vars, str);
			else if (*str != '\0')
				str = lexer_parse_text(curr, vars, str);
		}
		// printf("|%d|\n", trls_get_len(curr->treated_comnd));
		trls_print_list(curr->treated_comnd);
	}		
}

t_raw   *lexer_analysis(t_raw *root, t_vars *vars)
{
	if (root)
	{
		lexer_check_command(root, vars);
		lexer_check_flags(root);		
		lexer_parse_arg(root, vars);
	}
	
	return (0);
}