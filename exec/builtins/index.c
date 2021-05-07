/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:33:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/07 14:33:55 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	match_builtin(const char *s)
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

int	exec_builtins(t_exec *e, int idx, int job)
{
	pid_t	pid;
	//int		pid;
	int 	(*builtins[])(t_exec*) = {exec_builtin_env, exec_builtin_export, exec_builtin_pwd, exec_builtin_cd, exec_builtin_unset, exec_builtin_echo};

	pid = 0;
	if (e->count > 1)
		pid = fork();
		if (pid == -1)
			process_syserror();
		//fd0 = dup(0);
		//fd1 = dup(1);
	if (e->count > 1 && pid == 0)
	{
		restore_child_sig();
		pipes_redir(e, job);
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
	return (pid);
}
