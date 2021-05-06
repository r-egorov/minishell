
#include "exec.h"

static int	write_arr(char **arr, char *sep)
{
	if (!*arr)
		return (0);
	if (write(1, sep, ft_strlen(sep)) == -1)
		return (-1);
	if (write(1, *arr, ft_strlen(*arr)) == -1)
		return (-1);
	return (write_arr(arr + 1, " "));
}

int	exec_builtin_echo(t_exec *e)
{
	int		nl;

	//fprintf(stderr, "[echo]\n");
	nl = 0;
	if (e->argc >= 2)
	{
		if (eq(e->argv[1], "-n"))
			nl = 1;
		if (write_arr(e->argv + 1 + nl, "") == -1)
			return (FAIL);
	}
	if (!nl)
		if (write(1, "\n", 1) == -1)
			return (FAIL);
	return (OK);
}
