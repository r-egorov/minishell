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

void	exec_init(t_parser *p, t_exec *e)
{
	e->jobs = p->jobs;
	e->count = (int)p->jobs_len;
	e->fd = 0;
}

int	get_builtin_index(const char *s)
{
	const char	*cmds[] = {"env", "export", "pwd", "cd", "unset", "echo"};
	int			i;

	i = 0;
	while (i < (int)(sizeof(cmds) / sizeof(cmds[0])))
	{
		if (eq(cmds[i], s))
			return (i);
		i++;
	}
	return (-1);
}

int	exec_run(t_exec *e)
{
	pid_t	pid;
	int		i;
	int 	(*builtins[])(t_exec*) = {exec_builtin_env, exec_builtin_export, exec_builtin_pwd, exec_builtin_cd, exec_builtin_unset, exec_builtin_echo};
	int		idx;

	fprintf(stderr, "commands count: %d\n", e->count);
	e->fd = prepare_pipes(e->count - 1);
	i = e->count - 1;
	while (i >= 0)
	//i = 0;
	//while (i < e->count)
	{
		e->argc = e->jobs[i]->argc;
		e->argv = e->jobs[i]->argv;
		// check builtin function match
		idx = get_builtin_index(e->argv[0]);
		fprintf(stderr, "job: %d / %d, %s\n", i, e->count - 1, idx == -1 ? "[ ] builtin command" : "[x] builtin command");
		if (idx != -1)
		{	// builtin command
			if (e->count > 1)
				pid = fork();
				//fd0 = dup(0);
				//fd1 = dup(1);
			if (e->count > 1 && pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (i - 1 >= 0)
					dup2(e->fd[i - 1][0], 0), fprintf(stderr, "[builtin fork] job: %d / %d, dup2(fd[%d][0], 0)\n", i, e->count - 1, i - 1);
				if (i < e->count - 1)
					dup2(e->fd[i][1], 1), fprintf(stderr, "[builtin fork] job: %d / %d, dup2(fd[%d][1], 1)\n", i, e->count - 1, i);
				free_pipes(e->fd);
				builtins[idx](e);
				exit(0);
			}
			if (e->count == 1)
				builtins[idx](e);
			//dup2(fd0, 0);
			//dup2(fd1, 1);
			//close(fd0);
			//close(fd1);
			//fprintf(stderr, "restored fd 0 and 1\n");
		}
		else
		{
			// if not - run a command
			// Spawn a child to run the program
			pid = fork();
			if (pid == 0)
			{	// child
				//fprintf(stderr, "argv[0]: %s\n", e->argv[0]);
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (getenv("PATH") && find_command(&e->argv[0]) == FAIL)
				{
					printf("%s: %s\n", e->argv[0], ERR_COMMAND_NOT_FOUND);
					exit(127);
				}
				//fprintf(stderr, "argv[0]: %s\n", e->argv[0]);
				if (i - 1 >= 0)
					dup2(e->fd[i - 1][0], STDIN_FILENO), fprintf(stderr, "[command fork] job: %d / %d, dup2(fd[%d][0], 0)\n", i, e->count - 1, i - 1);
				if (i < e->count - 1)
					dup2(e->fd[i][1], STDOUT_FILENO), fprintf(stderr, "[command fork] job: %d / %d, dup2(fd[%d][1], 1)\n", i, e->count - 1, i);
				free_pipes(e->fd);
				execve(e->argv[0], e->argv, e->envp);
				printf("%s: %s: %s\n", APP_NAME, e->argv[0], strerror(errno));
				exit(127); // only if execv fails
			}
		}
		i--;
		//i++;
	}
	//dup2(STDIN_FILENO, 0);
	//dup2(STDOUT_FILENO, 1);
	free_pipes(e->fd);
	while (wait(0) != -1);
	//int st;
	//waitpid(pid, 0, 0); // wait for last child to exit
	//waitpid(pid, &st, 0); // wait for last child to exit
	//printf("errno: %d, stat: %d\n", errno, st);
	return (0);
}
