/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_function.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 21:28:41 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 12:56:52 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_FUNCTION_H
# define MY_FUNCTION_H
# define PWD_BUFF 1024

int		my_echo(t_raw *root);
int		my_pwd(void);
int		my_env(t_vars vars, t_raw *root);
int		my_unset(t_vars *vars, t_raw *root);
void	my_export_push_node(t_trls *list, t_vars *vars);
int		my_export_more(t_vars *vars, t_raw *root);
int		my_export(t_vars *vars, t_raw *root);
int		my_exit(t_vars *vars, t_raw *root);
int		my_cd(t_vars *vars, t_raw *root);
int		my_nondefault(t_vars *vars, t_raw *root);
int		my_nondefault_pipe(t_vars *vars, t_raw *root);
#endif