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



static void	print_all(t_exec *e)
{
	int		i;
	char	*key;
	char	*value;
	char	**arr;

	arr = get_copy_arr(e->envp);
	sort_array(arr);
	i = 0;
	while (arr[i])
	{
		key = get_key(arr[i]);
		if (!key)
			process_syserror();
		ft_putstr_fd(EXPORT_PREFIX, 1);
		ft_putstr_fd(key, 1);
		value = getenv(key);
		if (value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		free(key);
		i++;
	}
	free(arr);
}

int	exec_builtin_export(t_exec *e)
{
	extern char	**environ;
	char		**tmp;
	int			i;

	fprintf(stderr, "%s[builtin export] count: %d%s\n", BLT_COLOR, get_count(e->envp), DEFAULT);
	if (!e->argv[1])
	{
		print_all(e);
		return (0);
	}
	i = 1;
	while (e->argv[i])
	{
			tmp = env_add(e->envp, e->argv[i]);
			if (tmp && tmp != e->envp)
			{
				free(e->envp);
				e->envp = tmp;
				environ = tmp;
			}
		i++;
	}
    return (0);
}
