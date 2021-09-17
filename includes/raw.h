/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:37:04 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 10:30:16 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAW_H
# define RAW_H

t_raw	*raw_get_last(t_raw *root);
t_raw	*raw_new_node(void);
t_raw	*raw_push(t_raw *root, t_raw *new_node);
void	raw_free_node(t_raw *node);
void	raw_free_list(t_raw *root);
void	raw_print_list(t_raw *root);

#endif