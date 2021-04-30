/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:34:59 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/30 13:19:04 by lelderbe         ###   ########.fr       */
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
	char	*text;

	if (getenv("OLDPWD"))
	{
		// update
		text = ft_strjoin("OLDPWD=", oldpwd);
		if (!text)
			process_syserror();
		//env_update(e->envp, "OLDPWD", oldpwd);
		env_add(e->envp, text);
		free(text);
	}
	if (getenv("PWD"))
	{
		pwd = getcwd(0, 0);
		text = ft_strjoin("PWD=", pwd);
		if (!text)
			process_syserror();
		//env_update(e->envp, "PWD", pwd);
		free(pwd);
		env_add(e->envp, text);
		free(text);
	}
}

int	exec_builtin_cd(t_exec *e)
{
	int		result;
	char	*path;
	char	*dest;
	char	*oldpwd;

	if (e->argv[1] && e->argv[2])
	{
		printf("%s: %s: %s\n", SHELL_NAME, BUILTIN_CD_NAME, ERR_EXEC_CD_TOO_MANY_ARGS);
		process_error();
		return (FAIL);
	}
	if (e->argv[1])
		path = e->argv[1];
	else
		path = getenv("HOME");
		// what if null? (unset HOME)
 	if (!path)
		return (0);
	oldpwd = getcwd(0, 0);
	if (!oldpwd)
	{
		// error
		process_error();
		return (FAIL);
	}
	result = -1;
	dest = make_path(oldpwd, path);
	if (!dest)
	{
		// error
		free(oldpwd);
		process_error();
		return (FAIL);
	}
	result = chdir(dest);
	free(dest);
	if (result == -1)
	{
		// error
		free(oldpwd);
		return (FAIL);
	}
	update_env_vars(e, oldpwd);
	free(oldpwd);
	//current = getcwd(0, 0);
	//printf("new pwd: %s\n", current);
	//free(current);
	//printf("[cd] addr after : %p\n", e->envp);
	return (OK);
}

