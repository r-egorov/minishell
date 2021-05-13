#include "exec.h"

static int	is_digits_only(const char *s)
{
	if (ft_strlen(s) > 18)
		return (0);
	if (!(*s == '+' || *s == '-' || ft_isdigit(*s)))
		return (0);
	s++;
	while(*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	exec_builtin_exit(t_exec *e)
{
	ft_putendl_fd(BLTN_EXIT_NAME, 2);
	if (!e->argv[1])
		exit(e->status);
	if (!is_digits_only(e->argv[1]))
		exit(perr(BLTN_EXIT_NAME, e->argv[1], ERR_NUMERIC_REQ, 2));
	if (e->argv[2])
		return (perr(BLTN_EXIT_NAME, 0, ERR_TOO_MANY_ARGS, 1));
	exit((unsigned int)ft_atoi(e->argv[1]));
}
