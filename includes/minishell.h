/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:58:32 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/13 16:52:26 by jbenjy           ###   ########.fr       */
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
# include <sys/stat.h>
# include "../readline/history.h"
# include "../readline/readline.h"
// # include "readline/history.h"
// # include "readline/readline.h"
# include <dirent.h>
# include "defines.h"
# include "structures.h"
# include "my_function.h"
# include "../libft/libft.h"
# include <errno.h>
# include <sys/stat.h>
# include "libft_more.h"
# include "envp.h"
# include "redirect.h"
# include "raw.h"
# include "error.h"
# include "treated_list.h"

void	signal_int(int code);
void	signal_quit(int code);

int	    check_quotes(char *str);
int     is_dequote(char c);
int	    is_space(char c);
int	    is_special(char c);
char	*check_rct(t_redirect *curr_rct, char *str);


char	*find_command(char *str, t_raw *commands);
char	*find_flags(char *str, t_raw *command);
char	*find_arg(char *str, t_raw *commands);
char	*find_pipe(char *str, t_raw *command, int *check_type);

int     lexer_check_default_command(char *command);
int		lexer_check_path_command(char *command, t_vars *vars);
int		lexer_check_command(t_raw *curr, t_vars *vars);
int     lexer_check_flags(t_raw *curr);
void    lexer_analysis(t_raw *root, t_vars *vars);

void	main_loop(t_vars *vars);
int		init_envp(t_vars *vars, char **envp);

void	executor_loop(t_vars *vars, t_raw *root);
int		choose_executor(t_vars *vars, t_raw *root);

#endif