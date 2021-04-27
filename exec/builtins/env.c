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
	print_arr(e->envp);
	//print_arr(environ);
	return (0);
}
