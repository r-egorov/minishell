#include "exec.h"

char	*get_path(const char *s)
{
	char	*result;
	char	*path;
	char	**parts;
	char	*name;
	int		i;
	struct stat sb;

	result = 0;
	path = getenv("PATH");
	if (!path)
		return (0);
	//printf("path: %s\n", path);
	parts = ft_split(path, ':');
	if (!parts)
		process_syserror();
	//printf("=========\n");
	//print_arr(parts);
	//printf("=========\n");
	name = ft_strjoin("/", s);
	if (!name)
		process_syserror();
	i = 0;
	while (parts[i])
	{
		result = ft_strjoin(parts[i], name);
		if (!result)
			process_syserror();
		if (lstat(result, &sb) != -1)
		{	// file exists
			break ;
		}
		free(result);
		result = 0;
		i++;
	}
	free_split(parts);
	free(name);
	return (result);
}
