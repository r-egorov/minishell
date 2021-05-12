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
	fprintf(stderr, "%s[builtin env] count: %d%s\n", BLT_COLOR, get_count(e->envp), DEFAULT);
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
		fprintf(stderr, "%s[builtin env] getenv(%s) : %s%s\n", BLT_COLOR, e->argv[1], getenv(e->argv[1]), DEFAULT);
	//print_arr(environ);
	return (0);
}
