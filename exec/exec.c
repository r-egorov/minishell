/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:21:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/07 11:40:07 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_init(t_parser *p, t_exec *e)
{
	e->jobs = p->jobs;
	e->count = (int)p->jobs_len;
	e->fd = 0;
}

int	get_status_code(pid_t last)
{
	pid_t	pid;
	int		status;
	int		code;

	code = last;
	if (last == -1)
		return (1);
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
		{
			status = WTERMSIG(status) + 128;
			if (status == 131)
				ft_putstr_fd("Quit: 3\n", 2);
		}
		if (pid == last)
			code = status;
	}
	return (code);
}

pid_t	exec_command(t_exec *e, int job)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		process_syserror();
	if (pid == 0)
	{
		restore_child_sig();
		pipes_redir(e, job);
		if (fd_redir(e, job) == -1)
			exit(1);
		if (!e->argv)
			exit(0);
		if (getenv("PATH") && ft_strlen(getenv("PATH")) > 0 \
							&& find_command(&e->argv[0]) == FAIL)
			exit(perr(e->argv[0], 0, ERR_COMMAND_NOT_FOUND, 127));
		if (is_directory(e->argv[0]))
			exit(perr(e->argv[0], 0, ERR_IS_A_DIRECTORY, 126));
		execve(e->argv[0], e->argv, e->envp);
		if (errno == 13)
			exit(perr(e->argv[0], 0, strerror(errno), 126));
		exit(perr(e->argv[0], 0, strerror(errno), 127));
	}
	return (pid);
}

int	exec_run(t_exec *e)
{
	pid_t	pid;
	int		i;
	int		idx;
	pid_t	last;

	e->fd = create_pipes(e->count - 1);
	i = 0;
	while (i < e->count)
	{
		e->argc = e->jobs[i]->argc;
		e->argv = e->jobs[i]->argv;
		idx = -1;
		if (e->argv)
			idx = match_builtin(e->argv[0]);
		if (idx != -1)
			pid = exec_builtins(e, idx, i);
		else
			pid = exec_command(e, i);
		i++;
	}
	last = pid;
	free_pipes(e->fd);
	e->status = get_status_code(last);
	return (0);
}
