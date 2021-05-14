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
	const char	*cmds[] = {BLTN_ENV_NAME, BLTN_EXPORT_NAME, BLTN_PWD_NAME, \
				BLTN_CD_NAME, BLTN_UNSET_NAME, BLTN_ECHO_NAME, BLTN_EXIT_NAME};
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

static int	fork_builtin(t_exec *e, int (*f)(t_exec*), int job)
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
		exit(f(e));
	}
	return (0);
}

int	exec_builtins(t_exec *e, int idx, int job)
{
	int				code;
	int				fd0;
	int				fd1;
	const t_bltn	builtins[] = {
		exec_builtin_env, exec_builtin_export, exec_builtin_pwd,
		exec_builtin_cd, exec_builtin_unset, exec_builtin_echo,
		exec_builtin_exit
	};

	if (e->count > 1)
		return (fork_builtin(e, builtins[idx], job));
	fd0 = dup(STDIN_FILENO);
	fd1 = dup(STDOUT_FILENO);
	if (fd_redir(e, job) == -1)
		return (-1);
	code = builtins[idx](e);
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
	return (code);
}
