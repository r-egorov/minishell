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
	e->status = 0;
}

int	get_status_code(pid_t last)
{
	// int		loop;
	pid_t	pid;
	int		status;
	int		code;

	if (last == -1)
		return (1);
    while (1) {
        //pid = waitpid(-1, &status, WNOHANG);
        pid = wait(&status);
		code = 0;
		fprintf(stderr, "process %d finished, status code : %d, errno : %d\n", pid, status, errno);
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
			fprintf(stderr, "process %d WEXITSTATUS(status) : %d, errno : %d\n", pid, code, errno);
		}
		else
		{
			code = WTERMSIG(status);
			fprintf(stderr, "process %d WTERMSIG(status) : %d, errno : %d\n", pid, code, errno);
		}
        if (pid == last)
			return (code);
        if (pid <= 0)
			break;
    }
	return (0);
}

pid_t	exec_command(t_exec *e, int job)
{
	pid_t	pid;

	// Spawn a child to run the program
	pid = fork();
	if (pid == -1)
		process_syserror();
	if (pid == 0)	// child
	{
		//fprintf(stderr, "argv[0]: %s\n", e->argv[0]);
		restore_child_sig();
		//fprintf(stderr, "PATH: %s\n", getenv("PATH"));
		if (getenv("PATH") && find_command(&e->argv[0]) == FAIL)
		{
			printf("%s: %s\n", e->argv[0], ERR_COMMAND_NOT_FOUND);
			exit(127);
		}
		//fprintf(stderr, "argv[0]: %s\n", e->argv[0]);
		pipes_redir(e, job);
		// fd_redir(e, job);
		if (fd_redir(e, job) == -1)
			exit(1);
		execve(e->argv[0], e->argv, e->envp);
		printf("%s: %s: %s\n", APP_NAME, e->argv[0], strerror(errno));
		exit(127); // only if execv fails
	}
	return (pid);
}

int	exec_run(t_exec *e)
{
	pid_t	pid;
	int		i;
//	int 	(*builtins[])(t_exec*) = {exec_builtin_env, exec_builtin_export, exec_builtin_pwd, exec_builtin_cd, exec_builtin_unset, exec_builtin_echo};
	int		idx;
	pid_t	last;
	// int		status;
	// int		j;

	fprintf(stderr, "commands count: %d\n", e->count);
	e->fd = prepare_pipes(e->count - 1);
	//i = e->count - 1;
	//while (i >= 0)
	i = 0;
	while (i < e->count)
	{
		e->argc = e->jobs[i]->argc;
		e->argv = e->jobs[i]->argv;
		e->redir_in = e->jobs[i]->redir_in;
		e->redir_out = e->jobs[i]->redir_out;
		e->redir_append = e->jobs[i]->redir_append;
		// check builtin function match
		idx = match_builtin(e->argv[0]);
		fprintf(stderr, "job: %d / %d, %s\n", i, e->count - 1, idx == -1 ? "[ ] builtin command" : "[x] builtin command");
		if (idx != -1)	// builtin command
			pid = exec_builtins(e, idx, i);
		else	// if not - run a command
			pid = exec_command(e, i);
		//i--;
		i++;
		/*
		j = 0;
		while (j < 3)
		{
			sleep(1);
			j++;
		}
		*/
	}
	last = pid;
	//dup2(STDIN_FILENO, 0);
	//dup2(STDOUT_FILENO, 1);
	free_pipes(e->fd);
	e->status = get_status_code(last);
	fprintf(stderr, "Status code is : %d\n", e->status);
	//while (wait(0) != -1);
	//int st;
	//waitpid(pid, 0, 0); // wait for last child to exit
	//waitpid(pid, &st, 0); // wait for last child to exit
	//printf("errno: %d, stat: %d\n", errno, st);
	return (0);
}
