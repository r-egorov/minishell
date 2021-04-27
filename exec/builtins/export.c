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

int	exec_builtin_export(t_exec *e, char *param)
{
	char    **tmp;

	//printf("[export] addr before : %p\n", e->envp);
	//print_arr(e->envp, "environ --------------");
	tmp = env_add(e->envp, param);
	if (!tmp)
		return (-1); // error
	if (tmp != e->envp)
	{
        free(e->envp);
        e->envp = tmp;
	}
    //printf("[export] addr after : %p\n", e->envp);
    return (0);
}

