/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:55:38 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 15:21:45 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_close(t_pipes *pipes, int len)
{
	int	i;

	if (pipes->pids)
		free(pipes->pids);
	if (pipes->fds)
	{
		i = 0;
		while (i < len)
		{
			free(pipes->fds[i]);
			i++;
		}
		free(pipes->fds);
	}
}

int	pipe_exec(t_pipes *pipes, t_vars *vars, t_raw *curr)
{
	pipes->pids[pipes->i] = fork();
	if (pipes->pids[pipes->i] == -1)
		return (1);
	if (!pipes->pids[pipes->i])
	{
		if (!pipes->i)
			dup2(pipes->fds[pipes->i][1], STDOUT_FILENO);
		else if (pipes->i == pipes->len - 1)
			dup2(pipes->fds[pipes->i - 1][0], STDIN_FILENO);
		else
		{
			dup2(pipes->fds[pipes->i - 1][0], STDIN_FILENO);
			dup2(pipes->fds[pipes->i][1], STDOUT_FILENO);
		}
		close_all(pipes, pipes->len);
		exit(choose_executor_pipe(vars, curr));
	}
	return (1);
}

static void	pipes_loop_more(t_pipes	*pipes, t_vars *vars, t_raw *root)
{
	int		status;
	int		i;

	pipes->pids = 0;
	pipes->fds = 0;
	status = init_fds(pipes, pipes->len);
	status = init_pid(pipes, pipes->len);
	i = 0;
	while (i < pipes->len)
	{
		pipes->i = i;
		pipe_exec(pipes, vars, root);
		root = root->next;
		i++;
	}
	close_all(pipes, pipes->len);
	i = 0;
	while (i < pipes->len)
		waitpid(pipes->pids[i++], &status, 0);
	free_and_close(pipes, pipes->len);
}

int	pipes_loop(t_vars *vars, t_raw *root)
{
	t_pipes	pipes;
	int		status;

	pipes.len = count_pipes(root) + 1;
	status = 0;
	if (pipes.len != 1)
		pipes_loop_more(&pipes, vars, root);
	else
		choose_executor(vars, root);
	return (status);
}
