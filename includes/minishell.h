/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:58:32 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 15:54:43 by jbenjy           ###   ########.fr       */
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
void	signal_int_child(int code);
void	signal_exit_child(int code);

int		check_quotes(char *str);
int		is_dequote(char c);
int		is_space(char c);
int		is_special(char c);
char	*check_rct(t_redirect *curr_rct, char *str);

char	*find_command(char *str, t_raw *commands);
char	*find_flags(char *str, t_raw *command);
char	*find_arg(char *str, t_raw *commands);
char	*find_pipe(char *str, t_raw *command, int *check_type);

void	lexer_parse_redirect(t_raw *root, t_vars *vars);
void	lexer_parse_arg(t_raw *curr, t_vars *vars);
char	*lexer_parse_text(t_raw *curr, t_vars *vars, char *str);
char	*lexer_parse_dquote(t_raw *curr, t_vars *vars, char *str);
char	*lexer_parse_quote(t_raw *curr, char *str);
int		lexer_check_default_command(char *command);
int		lexer_check_path_command(char *command, t_vars *vars);
int		lexer_check_command(t_raw *curr, t_vars *vars);
int		lexer_check_flags(t_raw *curr);
void	lexer_analysis(t_raw *root, t_vars *vars);
char	*lexer_get_dollar(t_envp_list *envp, char *str, int dquote);
int		check_is_full_path_command(char *command);

void	main_loop(t_vars *vars);
int		init_envp(t_vars *vars, char **envp);

int		open_file(t_redirect	*list);
int		here_doc(t_redirect	*list);
int		count_pipes(t_raw *root);
int		error_free_fds(t_pipes *pipes, int len);
int		init_fds(t_pipes *pipes, int len);
int		init_pid(t_pipes *pipes, int len);
void	close_all(t_pipes *pipes, int len);

int		redirect_exec(t_raw *root, int *old_out, int *old_in);
int		pipes_loop(t_vars *vars, t_raw *root);

void	executor_loop(t_vars *vars, t_raw *root);
int		choose_executor(t_vars *vars, t_raw *root);
int		choose_executor_pipe(t_vars *vars, t_raw *root);

#endif