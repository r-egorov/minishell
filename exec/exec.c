/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:21:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/18 18:37:12 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	exec_run(t_parse *e)
{
	pid_t	pid;

	printf("[exec run] run this: %s\n", e->exec);
	// Spawn a child to run the program
	pid=fork();
	if (pid == 0) { // child process
		static char *argv[]={"ls", 0, NULL};
		execv(e->exec, argv);
		exit(127); // only if execv fails
	}
	else { // pid!=0; parent process
		waitpid(pid, 0, 0); // wait for child to exit
	}
	return (0);
}
