/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:59:54 by cisis             #+#    #+#             */
/*   Updated: 2021/04/15 18:16:46 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "main.h"
# include "line.h"

typedef struct	s_cli
{
	t_dlist			*history;
	struct termios	term;
	t_line			*line;

	char			*(*readline)(struct s_cli *self);
}				t_cli;

char 	*cli_readline(t_cli *self);
void	cli_init(t_cli *self);

#endif
