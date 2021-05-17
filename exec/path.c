/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:27:27 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 15:03:42 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (FAIL);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (OK);
	return (FAIL);
}

static char	*get_fullpath(char **parts, char *name)
{
	int			i;
	char		*result;
	struct stat	sb;

	result = 0;
	i = 0;
	while (parts[i])
	{
		result = ft_strjoin(parts[i], name);
		if (!result)
			process_syserror();
		if (stat(result, &sb) != -1 && ((sb.st_mode & S_IFMT) != S_IFDIR))
			break ;
		free(result);
		result = 0;
		i++;
	}
	return (result);
}

int	find_command(t_exec *e, char **s)
{
	char	*result;
	char	*path;
	char	**parts;
	char	*name;

	if (ft_strchr(*s, '/'))
		return (OK);
	path = get_env(e->env, "PATH");
	if (!path)
		return (FAIL);
	parts = ft_split(path, ':');
	if (!parts)
		process_syserror();
	name = ft_strjoin("/", *s);
	if (!name)
		process_syserror();
	result = get_fullpath(parts, name);
	free_split(parts);
	free(name);
	if (!result)
		return (FAIL);
	free(*s);
	*s = result;
	return (OK);
}

int	update_pwd(t_exec *e)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (pwd)
	{
		free(e->pwd);
		e->pwd = pwd;
		return (0);
	}
	else
		return (perr("getcwd", ERR_GETCWD_NO_DIR, strerror(errno), 1));
}
