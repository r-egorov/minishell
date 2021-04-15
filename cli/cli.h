#ifndef CLI_H
# define CLI_H

# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "main.h"

char 	*cli_readline(void);

typedef struct	s_line
{
	char		*str;
	int			len;
	void		(*append)(struct s_line *self, char *to_append, int size);
	char		(*pop_last)(struct s_line *self);
	void		(*del)(struct s_line *self);
}				t_line;

#endif
