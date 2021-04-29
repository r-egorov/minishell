/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:19:46 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 14:04:48 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_export(t_exec *e)
{
	extern char	**environ;
	char    **tmp;
	int		i;

	//printf("[export] addr before : %p | %p\n", e->envp, environ);
	//print_arr(e->envp, "environ --------------");
	i = 1;
	while (e->argv[i])
	{
		tmp = env_add(e->envp, e->argv[i]);
		/*
		if (!tmp)
		{
			process_error();
			return (-1); // error
		}
		*/
		if (tmp && tmp != e->envp)
		{
			//printf("[export] do free old envp\n");
			free(e->envp);
			e->envp = tmp;
			environ = tmp;
		}
		i++;
	}
    //printf("[export] addr after : %p | %p\n", e->envp, environ);
    return (0);
}

