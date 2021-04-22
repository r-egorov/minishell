/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:21:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 12:25:07 by lelderbe         ###   ########.fr       */
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
	pid_t		pid;
	extern char	**environ;
	//char	*s = "ZZ=ssssssss";
	//char	**tmp;


	printf("[exec run] run this: %s\n", e->exec);
	// Spawn a child to run the program
	printf("[exec run] environ addr  : %p\n", environ);
	printf("[exec run] environ count : %d\n", get_count(environ));
	printf("[exec run] getenv('ZZ')  : %s\n", getenv("ZZ"));
	if (eq(e->exec, "export"))
	{
		exec_builtin_export(0);
		return (0);
	}
	if (eq(e->exec, "unset"))
	{
		exec_builtin_unset("LANG");
		printf("environ addr after unset: %p\n", environ);
		return (0);
	}
	/*
	printf("environ addr : %p\n", environ);
	print_arr(environ, "parent environ ----------");
	//old_env = environ;
	tmp = env_add(environ, s);
	if (tmp)
	{
		free(environ);
		environ = tmp;
	}
	print_arr(environ, "ADDED environ ----------");
	tmp = env_remove(environ, "PWD");
	if (tmp)
	{
		free(environ);
		environ = tmp;
	}
	printf("environ addr: %p\n", environ);
	print_arr(environ, "REMOVED environ ----------");
	*/
	pid = fork();
	if (pid == -1)
	{
		// error happens
	}
	if (pid == 0)
	{
		// child process
		//printf("environ addr : %p\n", environ);
		//environ[28] = "ABC=aaaaaaaaaaaaaaaaaa";
		//print_arr(environ, "child environ ----------");
		char *argv[] = {e->exec, NULL};
		//char *envp[] = {"PATH=/usr/bin:/bin", "TEST=abc", NULL};
		char **envp = environ;
		//get_full_name(envp[0], e->exec);
		//execve(e->exec, argv, envp);
		execve(e->exec, argv, envp);
		printf("%d, %s\n", errno, strerror(errno));
		exit(127); // only if execv fails
	}
	else
	{
		// pid!=0; parent process
		waitpid(pid, 0, 0); // wait for child to exit
		//printf("%d, %s\n", errno, strerror(errno));
		//printf("environ addr : %p\n", environ);
		//print_arr(environ, "parent environ ----------");
	}
	return (0);
}
