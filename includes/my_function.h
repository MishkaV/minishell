/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_function.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 21:28:41 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/28 21:28:47 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_FUNCTION_H
# define MY_FUNCTION_H
# define PWD_BUFF 1024

int my_echo(char **str_mass);
int	my_pwd(char **str_mass);
int		my_env(t_vars vars, char **str_mass);

#endif