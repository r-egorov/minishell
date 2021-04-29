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

static char *make_path(char *part1, char *part2)
{
	char	*result;
	char	*tmp;

	result = 0;
	if (part2[0] == '/')
	{
		// absolute
		result = ft_strdup(part2);
		// if null?
		//printf("absolute path: %s\n", result);
		//result = chdir(path);
	}
	else
	{
		// relative
		tmp = ft_strjoin(part1, "/");
		if (!tmp)
			return (0);
		result = ft_strjoin(tmp, part2);
		free(tmp);
		//printf("relative path: %s\n", result);
		//if (!result)
		//	return (0);
	}
	return (result);
}

void	update_env_vars(t_exec *e, char *oldpwd)
{
	char	*pwd;

	if (getenv("OLDPWD"))
	{
		// update
		//pwd = ft_strjoin("OLDPWD=", oldpwd);
		//if (!pwd)
		//	; // error
		env_update(e->envp, "OLDPWD", oldpwd);
	}
	if (getenv("PWD"))
	{
		pwd = getcwd(0, 0);
		env_update(e->envp, "PWD", pwd);
	}
}

int	exec_builtin_cd(t_exec *e)
{
	int		result;
	char	*path;
	char	*dest;
	//char	*current;
	char	*oldpwd;

	if (e->argv[1] && e->argv[2])
	{
		printf("%s: %s: %s\n", SHELL_NAME, BUILTIN_CD_NAME, ERR_EXEC_CD_TOO_MANY_ARGS);
		return (FAIL);
	}

	if (e->argv[1])
		path = e->argv[1];
	else
		path = getenv("HOME");
		// what if null? (unset HOME)
 
	//printf("[cd] addr before : %p\n", e->envp);
	oldpwd = getcwd(0, 0);
	//printf("current dir: %s\n", current);
	if (!oldpwd)
	{
		// error
		return (FAIL);
	}
	result = -1;
	// if path = "" and unset HOME?
	dest = make_path(oldpwd, path);
	if (!dest)
	{
		// error
		return (FAIL);
	}
	result = chdir(dest);
	free(dest);
	if (result == -1)
	{
		// error
		return (FAIL);
	}
	update_env_vars(e, oldpwd);
	//current = getcwd(0, 0);
	//printf("new pwd: %s\n", current);
	//free(current);
	//printf("[cd] addr after : %p\n", e->envp);
	return (OK);
}

