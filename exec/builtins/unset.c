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

int	exec_builtin_unset(t_exec *e)
{
	extern char	**environ;
	//char	*result;
	char	**tmp;
	char	*key;
	
	printf("[unset] addr before : %p | %p\n", e->envp, environ);
	printf("[unset] PWD: %s\n", getenv("PWD"));
	if (e->argv[1])
	{
		key = e->argv[1];
		printf("[unset] getenv(key): %p\n", getenv(key));
		if (getenv(key))
		{
		//result = env_get(e->envp, key);
		//if (!result)
		//{
			// no key
			//return (0);
		//}
			printf("[unset] found key via getenv, now remove it\n");
			tmp = env_remove(e->envp, key);
			if (tmp)
			{
				free(e->envp);
				e->envp = tmp;
			}
		}
	}
	printf("[unset] addr after : %p | %p\n", e->envp, environ);
	printf("[unset] PWD: %s\n", getenv("PWD"));
	return (OK);
}
