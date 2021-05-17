/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:05:02 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 17:15:03 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_unset(t_exec *e)
{
	int	i;
	int	code;

	code = 0;
	i = 1;
	while (e->argv[i])
	{
		if (!is_valid_key(e->argv[i]))
			code = perr(BLTN_UNSET_NAME, e->argv[i], ERR_INVALID_ID, 1);
		else
			unset_env(&e->env, e->argv[i]);
		i++;
	}
	return (code);
}
