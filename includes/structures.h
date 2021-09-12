/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 20:32:33 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/12 10:24:47 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct				s_treated_list
{
	char					*arg;
	struct s_treated_list	*next;
}							t_trls;


typedef struct	s_command_info
{
	int			is_default;
	int			code;
}				t_command_info;

typedef struct			s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;

}						t_redirect;

typedef	struct		s_raw
{
	char			*command;
	char			*flags;
	char			*argument;
	int				type;
	t_redirect		*redirects;
	t_trls			*treated_comnd;
	t_command_info	command_info;
	struct s_raw	*next;
}					t_raw;

typedef struct  s_parse_flags
{
	int         exit;
}				t_parse_flags;

typedef struct          s_envp_list
{
	char                *key;
	char                *data;
	struct s_envp_list  *next;
}                       t_envp_list;

typedef struct  s_vars
{
	t_envp_list *envp;
	char		**paths;
}               t_vars;



#endif