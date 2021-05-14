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

int	find_command(char **s)
{
	char	*result;
	char	*path;
	char	**parts;
	char	*name;

	if (ft_strchr(*s, '/'))
		return (OK);
	path = getenv("PATH");
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

char	*get_pwd(t_exec *e)
{
	char	*result;

	result = getcwd(0, 0);
	if (result)
		return (result);
	perr("getcwd", "cannot access parent directories", strerror(errno), 1);
	return (e->pwd);
}
