#ifndef CLI_H
# define CLI_H

# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "main.h"

char 	*cli_readline(void);

#endif
