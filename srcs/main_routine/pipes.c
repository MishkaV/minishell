/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:55:38 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/15 15:30:45 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_pipes(t_raw *root)
{
	int count;

	count = 0;
	if (!root)
		return (0);
	if (root->type == TYPE_COMMAND)
		root = root->next;
	while (root && root->type == TYPE_PIPE)
	{
		count++;
		root = root->next;
	}
	return (count);
}

static int error_free_fds(t_pipes *pipes, int len)
{
	int i;

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
	return (1);   
}

static int init_fds(t_pipes *pipes, int len)
{
	int i;

	i = 0;
	pipes->fds = malloc(sizeof(int*) * (len));
	if (!pipes->fds)
		return (1);
	while (i < len)
	{
		pipes->fds[i] = malloc(sizeof(int) * 2);
		if (!pipes->fds[i])
			return (error_free_fds(pipes, i));
		if (pipe(pipes->fds[i]) == -1)
			return (error_free_fds(pipes, i));
		i++;
	}
	return (0);
}

static int init_pid(t_pipes *pipes, int len)
{
	pipes->pids = malloc(sizeof(int) * len);
	if (!pipes->pids)
		return (1);
	return (0);
}

static void close_all(t_pipes *pipes, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		close(pipes->fds[i][0]);
		close(pipes->fds[i][1]);
		i++;
	}
}

void    free_and_close(t_pipes *pipes, int len)
{
	int i;
	
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

int pipe_exec(t_pipes *pipes, t_vars *vars, t_raw *curr, int i, int len)
{
	pipes->pids[i] = fork();
	if (pipes->pids[i] == -1)
		return (1);
	if (!pipes->pids[i])
	{
		if (!i)
			dup2(pipes->fds[i][1], STDOUT_FILENO);
		else if (i == len - 1)
			dup2(pipes->fds[i - 1][0], STDIN_FILENO);
		else
		{
			dup2(pipes->fds[i - 1][0], STDIN_FILENO);
			dup2(pipes->fds[i][1], STDOUT_FILENO);
		}
		close_all(pipes, len);
		exit(choose_executor(vars, curr));
	}
	return (1);	
}

int pipes_loop(t_vars *vars, t_raw *root)
{
	t_pipes pipes;
	int     status;
	int     len;
	int     i;

	len = count_pipes(root) + 1;
	status = 0;
	if (len != 1)
	{
		pipes.pids = 0;
		pipes.fds = 0;
		status = init_fds(&pipes, len);
		status |= init_pid(&pipes, len);
		
		i = 0;
		while (i < len)
		{
			pipe_exec(&pipes, vars, root, i, len);
			root = root->next;
			i++;
		}

		close_all(&pipes, len);

		i = 0;
		while (i < len)
			waitpid(pipes.pids[i++], &status, 0);

		free_and_close(&pipes, len);
	}
	else
		choose_executor(vars, root);
	return (status);
}