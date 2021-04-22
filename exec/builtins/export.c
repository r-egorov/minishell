/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:19:46 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/21 16:14:04 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtin_export(char **argv)
{
	(void)argv;
	extern char	**environ;

	printf("[export] environ addr : %p\n", environ);
	print_arr(environ, "environ --------------");
}

void	exec_builtin_unset(char *key)
{
	extern char	**environ;
	char		*result;
	char		**tmp;

	printf("[unset] environ addr : %p\n", environ);
	if (!(result = getenv(key)))
	{
		return ;
	}
	tmp = env_remove(environ, key);
	if (tmp)
	{
		environ = tmp;
	}
	//print_arr(environ, "environ --------------");
}

