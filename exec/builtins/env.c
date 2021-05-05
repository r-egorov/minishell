/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:11:36 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 16:14:27 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_env(t_exec *e)
{
	//extern char **environ;

	//printf("[exec builtin env]\n");
	if (!e->envp)
	//if (!environ)
		return (0);
	fprintf(stderr, "count: %d\n", get_count(e->envp));
	print_arr(e->envp);

	/*
	if (eq(e->argv[1], "p"))
	{
		printf("-----------------------------------\n");
		print_arr(environ);
		printf("-----------------------------------\n");
		return (0);
	}
	*/
	if (e->argv[1])
		printf("[builtin env] getenv(%s) : %s\n", e->argv[1], getenv(e->argv[1]));
	//print_arr(environ);
	return (0);
}
