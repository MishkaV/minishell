/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:21:33 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/17 15:21:57 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_raw *root)
{
	int	count;

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

int	error_free_fds(t_pipes *pipes, int len)
{
	int	i;

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

int	init_fds(t_pipes *pipes, int len)
{
	int	i;

	i = 0;
	pipes->fds = malloc(sizeof(int *) * (len));
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

int	init_pid(t_pipes *pipes, int len)
{
	pipes->pids = malloc(sizeof(int) * len);
	if (!pipes->pids)
		return (1);
	return (0);
}

void	close_all(t_pipes *pipes, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		close(pipes->fds[i][0]);
		close(pipes->fds[i][1]);
		i++;
	}
}
