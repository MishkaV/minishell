/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:37 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/09 12:43:12 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////
// char	*lexer_parse_quote(char *str)
// {
	
// }

// char	*lexer_parse_dquote(char *str)
// {
	
// }

char	*lexer_get_dollar(t_envp_list *envp, char *str)
{
	char	*curr;
	char	*result;
	int		i;

	i = 0;
	if (!str)
		return (0);
	if(str[i] == '$')
		str++;
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
		result = lexer_get_dollar(vars->envp, str);
	else
		result = lexer_get_text(str);
	curr->treated_comnd = trls_push_node(curr->treated_comnd, result);
	return (skip_sym(str));
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
			// if (*str = "\'")
			// 	str = lexer_parse_quote(str);
			// else if (*str = "\"")
			// 	str = lexer_parse_dquote(str);
			// else
				str = lexer_parse_text(curr, vars, str);
		}
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