/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treated_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:51:06 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:34:23 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREATED_LIST_H
# define TREATED_LIST_H

t_trls	*trls_new_node(char *arg);
t_trls	*trls_push_node(t_trls *root, char *arg);
int		trls_get_len(t_trls *root);
void	trls_free_list(t_trls *root);
void	trls_print_list(t_trls *root);
#endif