/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:05:02 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/14 15:21:00 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
int	exec_builtin_unset(t_exec *e)
{
	extern char	**environ;
	char		**tmp;
	int			i;
	int			code;

	code = 0;
	i = 1;
	while (e->argv[i])
	{
		if (!is_valid_key(e->argv[i]))
			code = perr(BLTN_UNSET_NAME, e->argv[i], ERR_INVALID_ID, 1);
		else if (getenv(e->argv[i]))
		{
			tmp = env_remove(e->envp, e->argv[i]);
			if (tmp)
			{
				free(e->envp);
				e->envp = tmp;
				environ = tmp;
			}
		}
		i++;
	}
	return (code);
}
*/

int	exec_builtin_unset(t_exec *e)
{
	int			i;
	int			code;

	code = 0;
	i = 1;
	while (e->argv[i])
	{
		if (!is_valid_key(e->argv[i]))
			code = perr(BLTN_UNSET_NAME, e->argv[i], ERR_INVALID_ID, 1);
		else
			unset_env(e, e->argv[i]);
		i++;
	}
	return (code);
}
