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
		if (lstat(result, &sb) != -1)
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
