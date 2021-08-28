/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:58:32 by jbenjy            #+#    #+#             */
/*   Updated: 2021/08/27 21:39:17 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "structures.h"
# include "my_function.h"
# include "../libft/libft.h"
# include <errno.h>
# include <sys/stat.h>

int		ft_strcmp(const char *s1, const char *s2);
int		ft_find_chr(char *str, char c);
int 	ft_min(int n1, int n2);
int 	ft_max(int n1, int n2);
char	*ft_strndup(const char *s1, int n);

t_envp_list *envp_new_node(char *key, char *data);
t_envp_list *envp_push_node(t_envp_list *root, char *key, char *data);
char	    *envp_get_data(t_envp_list *root, char *key);
int	        envp_change_data(t_envp_list *root, char *key, char *data);
int			envp_free_node(t_envp_list *node);
int			envp_free_list(t_envp_list *root);
t_envp_list	*envp_pop_front(t_envp_list *root);
t_envp_list *envp_pop_by_key(t_envp_list *root, char *key);
void	envp_print_list(t_envp_list	*root);

void	main_loop();
int		init_envp(t_vars *vars, char **envp);
// void    free_all(t_vars *vars);

#endif