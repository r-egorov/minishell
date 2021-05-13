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
	int		i;
	char	*value;

	if (!e->envp)
		return (0);
	fprintf(stderr, "%s[builtin env] count: %d%s\n", BLT_COLOR, get_count(e->envp), DEFAULT);
	i = 0;
	while (e->envp[i])
	{
		value = get_value(e->envp[i]);
		if (value)
		{
			free(value);
			printf("%s\n", e->envp[i]);
		}
		i++;
	}
	return (0);
}
