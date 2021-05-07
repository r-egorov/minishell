/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:21:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/06 16:21:05 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_pipes(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	**prepare_pipes(int n)
{
	int	**result;
	int	i;

	result = malloc(sizeof(*result) * (n + 1));
	if (!result)
		process_syserror();
	fprintf(stderr, "create pipes ------------\n");
	i = 0;
	while (i < n)
	{
		result[i] = malloc(sizeof(**result) * 2);
		if (!result)
			process_syserror();
		if ((pipe(result[i])) == -1)
			process_syserror();
		fprintf(stderr, "pipe %d : fd[%d][0]: %d, fd[%d][1]: %d\n", i, i, result[i][0], i, result[i][1]);
		i++;
	}
	fprintf(stderr, "done --------------------\n");
	result[i] = 0;
	return (result);
}

void	pipes_redir(t_exec *e, int job)
{
	if (job - 1 >= 0)
		dup2(e->fd[job - 1][0], 0), fprintf(stderr, "[builtin fork] job: %d / %d, dup2(fd[%d][0], 0)\n", job, e->count - 1, job - 1);
	if (job < e->count - 1)
		dup2(e->fd[job][1], 1), fprintf(stderr, "[builtin fork] job: %d / %d, dup2(fd[%d][1], 1)\n", job, e->count - 1, job);
	free_pipes(e->fd);
}
