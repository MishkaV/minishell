/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/09 21:19:22 by jbenjy           ###   ########.fr       */
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

// Внутри могут быть скобки!!!
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


static char	*lexer_dquote_ret(char *result, char *str, int i)
{
	char	*str1;
	char	*str2;

	str1 = result;
	str2 = ft_strndup(str, i);
	result = ft_concat(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (result);
}

char	*lexer_parse_dquote(t_raw *curr, t_vars *vars, char *str)
{
	int		i;
	char	*result;
	char	*path;
	
	
	i = 0;
	result = 0;
	if (*str == '\"')
		str++;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			path = lexer_get_dollar(vars->envp, str + i, 1);
			if (path)
			{
				result = ft_concat(result,  path);
				free(path);
			}
			while (str[i] && !is_space(str[i]) && str[i] != '\"')
				i++;
			str += i;
			i = 0;
		}
		else if (str[i] == '\\' && is_dequote(str[i + 1]))
		{
			puts("IN");
			printf("%c = %d\n", str[i+1], is_dequote(str[i+1]));
			char *str_before;
			if (i)
				str_before = ft_strndup(str, i - 1);
			else
				str_before = ft_strdup("");
			char *str_after = ft_strdup(str + i + 1);
			str = ft_concat(str_before, str_after);
			free(str_before);
			free(str_after);
			i--;
		}
		else
			i++;
	}
	curr->treated_comnd = trls_push_node(curr->treated_comnd,
							lexer_dquote_ret(result, str, i));
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