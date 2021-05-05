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
	e->exec = p->exec;
	e->argv = p->argv;
}

static void	close_fds(int **fd, int n)
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
	{
		process_syserror();
	}
	i = 0;
	while (i < n)
	{
		result[i] = malloc(sizeof(**result) * 2);
		if (!result)
		{
			process_syserror();
		}
		if ((pipe(result[i])) == -1)
			process_syserror();
		printf("pipe %d : fd[%d][0]: %d, fd[%d][1]: %d\n", i, i, result[i][0], i, result[i][1]);
		i++;
	}
	return (result);
}

int	exec_run(t_exec *e)
{
	//extern char	**environ;
	pid_t		pid;
	int **fd;
	int	i;
	int	count;
	char	*cmd;

	//pipe(fd);
	//printf("fd0: %d, fd[1]: %d\n", fd[0], fd[1]);

	//printf("----------\n");
	//print_arr(e->argv);
	//printf("----------\n");
	//printf("[exec run] run this: %s\n", e->exec);
	//printf("env_get('PWD') : %s\n", env_get(e->envp, "PWD"));
	// Spawn a child to run the program
	if (eq(e->argv[0], "env"))
	{
		exec_builtin_env(e);
		return (0);
	}
	if (eq(e->argv[0], "cd"))
	{
		exec_builtin_cd(e);
		return (0);
	}
	if (eq(e->argv[0], "pwd"))
	{
		exec_builtin_pwd(e);
		return (0);
	}
	if (eq(e->argv[0], "export"))
	{
		exec_builtin_export(e);
		return (0);
	}
	if (eq(e->argv[0], "unset"))
	{
		exec_builtin_unset(e);
		//printf("environ addr after unset: %p\n", environ);
		return (0);
	}

	count = get_count(e->argv);
	printf("commands count: %d\n", count);
	fd = prepare_pipes(count - 1);

	i = 0;
	while (i < count)
	{
		pid = fork();
		if (pid == 0)
		{	// child
			printf("argv[i]: %s\n", e->argv[i]);
			if (!ft_strchr(e->argv[i], '/'))
			{
				cmd = get_path(e->argv[i]);
				if (cmd)
				{
					free(e->argv[i]);
					e->argv[i] = cmd;
				}
				
				if (!cmd)
				{
					printf("%s: %s\n", e->argv[i], ERR_COMMAND_NOT_FOUND);
					exit(127);
				}
				
				//	cmd = e->argv[i];
			}
			printf("argv[i]: %s\n", e->argv[i]);
			if (i - 1 >= 0)
			{
				printf("i: %d, dup2(fd[%d][0], 0)\n", i, i - 1);
				dup2(fd[i - 1][0], 0);
			}			
			if (i < count - 1)
			{
				printf("i: %d, dup2(fd[%d][1], 1)\n", i, i);
				dup2(fd[i][1], 1);
			}
			close_fds(fd, count - 1);
			//char *argv[] = {e->argv[i], NULL};
			char *argv[] = {e->argv[i], NULL};
			//execve(e->argv[i], argv, e->envp);
			execve(e->argv[i], argv, e->envp);
			printf("%s: %s\n", APP_NAME, strerror(errno));
			// free fd?
			exit(127); // only if execv fails
		}
		i++;
	}
	close_fds(fd, count - 1);
	waitpid(pid, 0, 0); // wait for last child to exit

/*
	if (pid == 0)
	{
		// child process
		char *argv[] = {e->exec, NULL};
		//char *envp[] = {"PATH=/usr/bin:/bin", "TEST=abc", NULL};
		//char **envp = e->envp;
		//get_full_name(envp[0], e->exec);
		//execve(e->exec, argv, envp);
		execve(e->exec, argv, e->envp);
		//execve(e->exec, e->argv, environ);
		//printf("%d, %s\n", errno, strerror(errno));
		printf("%s: %s\n", APP_NAME, strerror(errno));
		exit(127); // only if execv fails
	}
*/

	return (0);
}
