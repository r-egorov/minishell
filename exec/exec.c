/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:21:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/30 13:20:24 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_init(t_parser *p, t_exec *e)
{
	e->jobs = p->jobs;
	e->jobs_len = p->jobs_len;
}

static void	free_pipes(int **fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		i++;
	}
	free(fd);
}

static int	**prepare_pipes(int n)
{
	int	**result;
	int	i;

	result = malloc(sizeof(*result) * n);
	if (!result)
		process_syserror();
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
	return (result);
}

int	get_builtin_index(const char *s)
{
	const char	*cmds[] = {"env", "export", "pwd", "cd", "unset"};
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
	int		**fd;
	int		i;
	int		count;
	int 	(*builtins[])(t_exec*) = {exec_builtin_env, exec_builtin_export, exec_builtin_pwd, exec_builtin_cd, exec_builtin_unset};
	int		idx;
	//int		fd0;
	int		fd1;

	count = (int)e->jobs_len;
	fprintf(stderr, "commands count: %d\n", count);
	fd = prepare_pipes(count - 1);

	i = 0;
	while (i < count)
	{
		e->argv = e->jobs[i]->argv;
		fprintf(stderr, "i : %d, jobs_len : %d\n", i, count);
		//print_arr(e->argv);
	
		// check builtin function match
		idx = get_builtin_index(e->argv[0]);
		fprintf(stderr, "index : %d\n", idx);
		if (idx != -1)
		{
			wait(0);
				//fd0 = dup(0);
				fd1 = dup(1);
				if (i - 1 >= 0)
				{
					//fprintf(stderr, "[bt] i: %d, dup2(fd[%d][0], 0)\n", i, i - 1);
					//dup2(fd[i - 1][0], 0);
				}			
				if (i < count - 1)
				{
					fprintf(stderr, "[bt] i: %d, dup2(fd[%d][1], 1)\n", i, i);
					dup2(fd[i][1], 1);
				}
			builtins[idx](e);
			//close(1);
			//close(fd[0][1]);
			//close(0);
			fflush(stdout);
			//dup2(fd0, 0);
			dup2(fd1, 1);
			//close(fd0);
			close(fd1);
			fprintf(stderr, "restored fd 0 and 1\n");
			//return (0);
		}
		else
		{
			// if not - run a command
			// Spawn a child to run the program
			pid = fork();
			if (pid == 0)
			{	// child
				//fprintf(stderr, "argv[0]: %s\n", e->argv[0]);
				//fprintf(stderr, "reset signal: %s\n", signal(SIGINT, SIG_DFL));
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (find_command(&e->argv[0]) == FAIL)
				{
					fprintf(stderr, "%s: %s\n", e->argv[0], ERR_COMMAND_NOT_FOUND);
					exit(127);
				}
				//fprintf(stderr, "argv[0]: %s\n", e->argv[0]);
				if (i - 1 >= 0)
				{
					fprintf(stderr, "[child] i: %d, dup2(fd[%d][0], 0)\n", i, i - 1);
					dup2(fd[i - 1][0], STDIN_FILENO);
				}			
				if (i < count - 1)
				{
					fprintf(stderr, "[child] i: %d, dup2(fd[%d][1], 1)\n", i, i);
					dup2(fd[i][1], STDOUT_FILENO);
				}
				free_pipes(fd, count - 1);
				//char *argv[] = {e->argv[i], NULL};
				//execve(e->argv[i], argv, e->envp);
				execve(e->argv[0], e->argv, e->envp);
				fprintf(stderr, "%s: %s\n", APP_NAME, strerror(errno));
				// free fd?
				exit(127); // only if execv fails
			}
		}
		//wait(0); // wait for last child to exit
		i++;
	}
	//dup2(STDIN_FILENO, 0);
	//dup2(STDOUT_FILENO, 1);
	free_pipes(fd, count - 1);
	waitpid(pid, 0, 0); // wait for last child to exit
	return (0);
}
