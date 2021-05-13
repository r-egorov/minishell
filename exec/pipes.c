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

int	**create_pipes(int n)
{
	int	**result;
	int	i;

	result = malloc(sizeof(*result) * (n + 1));
	if (!result)
		process_syserror();
	// fprintf(stderr, "%screate pipes ------------%s\n", PCOLOR, DEFAULT);
	i = 0;
	while (i < n)
	{
		result[i] = malloc(sizeof(**result) * 2);
		if (!result)
			process_syserror();
		if ((pipe(result[i])) == -1)
			process_syserror();
		// fprintf(stderr, "%spipe %d : fd[%d][0]: %d, fd[%d][1]: %d%s\n", PCOLOR, i, i, result[i][0], i, result[i][1], DEFAULT);
		i++;
	}
	// fprintf(stderr, "%sdone --------------------%s\n", PCOLOR, DEFAULT);
	result[i] = 0;
	return (result);
}

void	pipes_redir(t_exec *e, int job)
{
	int	result;

	if (job - 1 >= 0)
	{
		result = dup2(e->fd[job - 1][0], 0);
		// fprintf(stderr, "%s[fork] pipe redir for job: %d / %d, fd[%d][0] => 0%s\n", PCOLOR, job, e->count - 1, job - 1, DEFAULT);
		if (result == -1)
			process_syserror();
	}
	if (job < e->count - 1)
	{
		result = dup2(e->fd[job][1], 1);
		// fprintf(stderr, "%s[fork] pipe redir for job: %d / %d, fd[%d][1] => 1%s\n", PCOLOR, job, e->count - 1, job, DEFAULT);
		if (result == -1)
			process_syserror();
	}
	free_pipes(e->fd);
}
