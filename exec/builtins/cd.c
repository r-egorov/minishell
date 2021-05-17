/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:34:59 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/17 14:31:35 by lelderbe         ###   ########.fr       */
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

static void	update_env_vars(t_exec *e)
{
	if (find_by_key(e->env, "OLDPWD"))
	{
		if (find_by_key(e->env, "PWD"))
			update_by_key(e->env, "OLDPWD", \
				get_env(e->env, "PWD"), EXPORT_UPDATE);
		else
			update_by_key(e->env, "OLDPWD", e->pwd, EXPORT_UPDATE);
	}
	update_pwd(e);
	if (find_by_key(e->env, "PWD"))
		update_by_key(e->env, "PWD", e->pwd, EXPORT_UPDATE);
}

static int	parse_arg(t_exec *e, char **path, int *run_pwd)
{
	*run_pwd = 0;
	*path = get_env(e->env, "HOME");
	if (!e->argv[1])
	{
		if (!*path)
			return (perr(BLTN_CD_NAME, NULL, ERR_CD_HOME_NOT_SET, 1));
	}
	else
	{
		*path = e->argv[1];
		if (eq(e->argv[1], "-"))
		{
			*path = get_env(e->env, "OLDPWD");
			if (!*path)
				return (perr(BLTN_CD_NAME, NULL, ERR_CD_OLDPWD_NOT_SET, 1));
			*run_pwd = 1;
		}
	}
	return (0);
}

int	exec_builtin_cd(t_exec *e)
{
	int		code;
	char	*path;
	int		run_pwd;
	char	*dest;

	code = parse_arg(e, &path, &run_pwd);
	if (code)
		return (code);
	dest = make_path(e->pwd, path);
	if (chdir(dest) == -1)
	{
		free(dest);
		return (perr(BLTN_CD_NAME, path, strerror(errno), 1));
	}
	free(dest);
	update_env_vars(e);
	if (run_pwd)
		return (exec_builtin_pwd(e));
	return (0);
}
