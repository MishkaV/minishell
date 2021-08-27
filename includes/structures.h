/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 20:32:33 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/26 12:08:15 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
}               t_vars;



#endif