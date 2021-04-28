/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:34:59 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/28 13:06:17 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_cd(t_exec *e, char *path)
{
	char	*pwd;
	char	*tmp;
	int		result;

	(void)e;
	//printf("[cd] addr before : %p\n", e->envp);
	pwd = getcwd(0, 0);
	printf("pwd: %s\n", pwd);
	if (!pwd)
	{
		// error
		return (FAIL);
	}
	result = -1;
	if (path[0] == '/')
	{
		// absolute
		free(pwd);
		printf("absolute: %s\n", path);
		result = chdir(path);
	}
	else
	{
		tmp = ft_strjoin(pwd, "/");
		free(pwd);
		pwd = ft_strjoin(tmp, path);
		free(tmp);
		printf("relative: %s\n", pwd);
		result = chdir(pwd);
		free(pwd);
	}
	//result = chdir(path);
	if (result == -1)
	{
		// error
		return (FAIL);
	}
	pwd = getcwd(0, 0);
	printf("finally pwd: %s\n", pwd);
	free(pwd);
	//printf("[cd] addr after : %p\n", e->envp);
	return (OK);
}

