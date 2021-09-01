/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_more.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:36:01 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/31 13:36:34 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MORE_H
# define LIBFT_MORE_H

int		ft_strcmp(const char *s1, const char *s2);
int		ft_find_chr(char *str, char c);
char	*ft_concat(char *s1, char *s2);
char	*ft_strndup(const char *s1, int n);
char	*skip_spaces(char *str);

#endif