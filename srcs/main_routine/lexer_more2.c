/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_more2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:43:03 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 14:44:11 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_analysis(t_raw *root, t_vars *vars)
{
	if (root)
	{
		while (root)
		{
			lexer_check_command(root, vars);
			lexer_parse_arg(root, vars);
			lexer_parse_redirect(root, vars);
			root = root->next;
		}
	}
}

void	lexer_parse_arg(t_raw *curr, t_vars *vars)
{
	char	*str;

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
