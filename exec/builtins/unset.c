/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:05:02 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 14:32:58 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_unset(t_exec *e, char *key)
{
	char	*result;
	char	**tmp;

	printf("[unset] addr before : %p\n", e->envp);
	result = env_get(e->envp, key);
	if (!result)
	{
		// no key
		return (-1);
	}
	tmp = env_remove(e->envp, key);
	if (tmp)
	{
		free(e->envp);
		e->envp = tmp;
	}
	printf("[unset] addr after : %p\n", e->envp);
	return (0);
}

