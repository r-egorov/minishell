/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:34:59 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/14 20:02:22 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*cut_last_dir(char *s, const char *part2)
{
	char	*result;
	char	*ptr;

	result = 0;
	if (!eq(part2, ".."))
		return (0);
	ptr = 0;
	ptr = ft_strrchr(s, '/');
	if (ptr)
		*ptr = '\0';
	if (ft_strlen(s) == 0)
		result = ft_strdup("/");
	else
		result = ft_strdup(s);
	if (!result)
		process_syserror();
	if (ptr)
		*ptr = '/';
	return (result);
}

static char	*make_path(char *part1, char *part2)
{
	char	*result;
	char	*tmp;

	result = 0;
	if (part2[0] == '/')
	{
		result = ft_strdup(part2);
		if (!result)
			process_syserror();
	}
	else
	{
		result = cut_last_dir(part1, part2);
		if (!result)
		{
			tmp = ft_strjoin(part1, "/");
			if (!tmp)
				process_syserror();
			result = ft_strjoin(tmp, part2);
			free(tmp);
			if (!result)
				process_syserror();
		}
	}
	return (result);
}

static void	update_pwd_variable(t_exec *e)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (pwd)
	{
		free(e->pwd);
		e->pwd = pwd;
	}
}

static void	update_env_vars(t_exec *e)
{
	char	*text;

	if (find(e->envp, "OLDPWD"))
	{
		if (find(e->envp, "PWD"))
			text = ft_strjoin("OLDPWD=", getenv("PWD"));
		else
			text = ft_strjoin("OLDPWD=", e->pwd);
		if (!text)
			process_syserror();
		env_add(e->envp, text);
		free(text);
	}
	update_pwd_variable(e);
	if (find(e->envp, "PWD"))
	{
		text = ft_strjoin("PWD=", e->pwd);
		if (!text)
			process_syserror();
		env_add(e->envp, text);
		free(text);
	}
}

int	exec_builtin_cd(t_exec *e)
{
	int		result;
	char	*path;
	char	*dest;

	if (e->argv[1])
		path = e->argv[1];
	else
		path = getenv("HOME");
	if (!path)
		return (perr(BLTN_CD_NAME, NULL, ERR_CD_HOME_NOT_SET, 1));
	dest = make_path(e->pwd, path);
	result = chdir(dest);
	if (result == -1)
	{
		free(dest);
		return (perr(BLTN_CD_NAME, path, strerror(errno), 1));
	}
	update_env_vars(e);
	free(dest);
	return (0);
}
