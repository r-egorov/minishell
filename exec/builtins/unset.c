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

static int	is_valid_key(char *key)
{
	int		i;

	i = 0;
	while (key[i])
	{
		if (i == 0 && ft_isdigit(key[i]))
			return (FAIL);
		if (!(ft_strchr("_", key[i]) || ft_isalnum(key[i])))
			return (FAIL);
		i++;
	}
	return (OK);
}

int	exec_builtin_unset(t_exec *e)
{
	extern char	**environ;
	char		**tmp;
	char		*key;
	int			i;
	
	//fprintf(stderr, "[unset] addr before : %p | %p\n", e->envp, environ);
	i = 1;
	while (e->argv[i])
	{
		key = e->argv[i];
		//fprintf(stderr, "[unset] getenv(key): %p\n", getenv(key));
		if (is_valid_key(key) == FAIL)
		{
			printf("%s: %s: `%s': %s\n", APP_NAME, BUILTIN_UNSET_NAME, key, ERR_EXEC_UNSET_INVALID_ID);
		}
		else if (getenv(key))
		{
			//fprintf(stderr, "[unset] found key via getenv, now remove it\n");
			tmp = env_remove(e->envp, key);
			if (tmp)
			{
				free(e->envp);
				e->envp = tmp;
				environ = tmp;
			}
		}
		i++;
	}
	//fprintf(stderr, "[unset] addr after : %p | %p\n", e->envp, environ);
	return (OK);
}
