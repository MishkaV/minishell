/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_function.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 21:28:41 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/16 20:51:22 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_FUNCTION_H
# define MY_FUNCTION_H
# define PWD_BUFF 1024

int my_echo(t_raw *root);
int	my_pwd(void);
int	my_env(t_vars vars, t_raw *root);
int	my_unset(t_vars *vars, t_raw *root);
int	my_export(t_vars *vars, t_raw *root);
int	my_exit(t_vars *vars, t_raw *root);
int my_cd(t_vars *vars, t_raw *root);
int my_nondefault(t_vars *vars, t_raw *root);

#endif