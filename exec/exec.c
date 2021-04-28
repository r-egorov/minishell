/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:21:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/28 13:07:39 by lelderbe         ###   ########.fr       */
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


	//printf("[exec run] run this: %s\n", e->exec);
	//printf("env_get('PWD') : %s\n", env_get(e->envp, "PWD"));
	// Spawn a child to run the program
	if (eq(e->exec, "cd"))
	{
		exec_builtin_cd(e, "../..");
		return (0);
	}
	if (eq(e->exec, "env"))
	{
		exec_builtin_env(e);
		return (0);
	}
	if (eq(e->exec, "pwd"))
	{
		exec_builtin_pwd(e);
		return (0);
	}
	if (eq(e->exec, "export"))
	{
		exec_builtin_export(e, "ZZ=zzz:");
		return (0);
	}
	if (eq(e->exec, "unset"))
	{
		exec_builtin_unset(e, "PWD");
		//printf("environ addr after unset: %p\n", environ);
		return (0);
	}
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
		printf("%d, %s\n", errno, strerror(errno));
		exit(127); // only if execv fails
	}
	else
	{
		// pid!=0; parent process
		waitpid(pid, 0, 0); // wait for child to exit
		//printf("%d, %s\n", errno, strerror(errno));
	}
	return (0);
}
