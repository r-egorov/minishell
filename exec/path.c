#include "exec.h"

static char *get_fullpath(char **parts, char *name)
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
		// if (lstat(result, &sb) != -1)
		if (stat(result, &sb) != -1)
			break ;
		free(result);
		result = 0;
		i++;
	}
	fprintf(stderr, "st_mode: %d & IFMT: %d ==> %d | %d <== Regular file (S_IFREG)\n", sb.st_mode, S_IFMT, sb.st_mode & S_IFMT, S_IFREG);
	if (result && ((sb.st_mode & S_IFMT) != S_IFREG))
		return (0);
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
	//printf("path: %s\n", path);
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
