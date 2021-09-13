/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:53:21 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 17:11:36 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

t_redirect  *rct_get_last(t_redirect  *root);
t_redirect  *rct_new_node();
t_redirect	*rct_push(t_redirect *root, t_redirect *new_node);
void	rct_print(t_redirect *root);
void	rct_free_node(t_redirect *node);
void	rct_free_list(t_redirect *root);

#endif