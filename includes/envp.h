/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:35:17 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:26:55 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

t_envp_list	*envp_new_node(char *key, char *data);
t_envp_list	*envp_push_node(t_envp_list *root, char *key, char *data);
char		*envp_get_data(t_envp_list *root, char *key);
int			envp_change_data(t_envp_list *root, char *key, char *data);
int			envp_free_node(t_envp_list *node);
int			envp_free_list(t_envp_list *root);
t_envp_list	*envp_pop_front(t_envp_list *root);
t_envp_list	*envp_pop_by_key(t_envp_list *root, char *key);
void		envp_print_list(t_envp_list	*root);
t_envp_list	*envp_copy_list(t_envp_list *root);
char		**envp_to_char(t_envp_list *root);
int			envp_get_len(t_envp_list *root);

#endif