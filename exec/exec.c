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

char *get_full_name(char *path, char *name)
{
	char	**parts;
	int		i;

	(void)name;
	parts = ft_split(path, ':');
	if (!parts)
	{
		//free_split(parts);
		printf("error while split $PATH\n");
	}
	i = 0;
	while (parts[i])
	{
		printf("parts[%d]: %s\n", i, parts[i]);
		i++;
	}
	return (0);
}

void	exec_init(t_parser *p, t_exec *e)
{
	e->exec = p->exec;
	e->argv = p->argv;
}

int	exec_run(t_exec *e)
{
	//extern char	**environ;
	pid_t		pid;
	//int fd[2];
	int **fd;
	int	i;
	int	j;
	int	count;

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
	printf("cmds count: %d\n", count);

	fd = malloc(sizeof(*fd) * (count - 1));
	// error
	i = 0;
	while (i < count - 1)
	{
		fd[i] = malloc(sizeof(**fd) * 2);
		// error
		pipe(fd[i]);
		printf("fd[%d][0]: %d, fd[%d][1]: %d\n", i, fd[i][0], i, fd[i][1]);
		i++;
	}

	i = 0;
	while (i < count)
	{
		pid = fork();
		if (pid == 0)
		{	// child
			if (i - 1 >= 0)
			{
				printf("i - 1: %d, dup2(fd[%d][0], 0)\n", i - 1, i - 1);
				dup2(fd[i - 1][0], 0);
			}			
			if (i < count - 1)
			{
				printf("i: %d, dup2(fd[%d][1], 1)\n", i, i);
				dup2(fd[i][1], 1);
			}

			/*
			if (i != 0)
			{
				printf("i: %d, dup2(fd[0], 0)\n", i);
				dup2(fd[0], 0);
			}
			if (i != count - 1)
			{
				printf("i: %d, dup2(fd[1], 1)\n", i);
				dup2(fd[1], 1);
			}
			*/

			j = 0;
			while (j < count - 1)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			char *argv[] = {e->argv[i], NULL};
			execve(e->argv[i], argv, e->envp);
			printf("%s: %s\n", APP_NAME, strerror(errno));
			exit(127); // only if execv fails
		}
		i++;
	}
	//close(fd[0]);
	//close(fd[1]);
	j = 0;
	while (j < count - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	waitpid(pid, 0, 0); // wait for last child to exit

/*
	pid = fork();
	if (pid == -1)
	{
		// error happens
	}
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
	else
	{
		// pid!=0; parent process
		waitpid(pid, 0, 0); // wait for child to exit
		//printf("%d, %s\n", errno, strerror(errno));
	}
*/

	return (0);
}
