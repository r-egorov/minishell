/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:21:30 by cisis             #+#    #+#             */
/*   Updated: 2021/04/16 13:56:37 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void	cli_init(t_cli *self)
{
	self->history = NULL;
	self->readline = cli_readline;
	self->line = line_new();
}

void	cli_del(t_cli *self)
{
	self->line->del(self->line);
}

void	cli_launch_term(t_cli *self)
{
	tcgetattr(0, &(self->term));
	self->term.c_lflag &= ~(ECHO);
	self->term.c_lflag &= ~(ICANON);

	if (tcsetattr(0, TCSANOW, &self->term) == -1)
		process_error();

	if (tgetent(0, "xterm-256color") == -1)
		process_error();

	write(1, "minihell > ", 11);
	
	tputs(save_cursor, 1, ft_putchar);
}

static void	handle_up_down(char *buf)
{
	if (!ft_strncmp(buf, "\e[A", 3))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		write(1, "UP", 2);
	}
	else if (!ft_strncmp(buf, "\e[B", 3))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		write(1, "DOWN", 4);
	}
}

static void handle_backspace(t_cli *self)
{
	if ((self->line->pop_last(self->line)))
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
}

char 	*cli_readline(t_cli *self)
{
	int 			nbytes;
	int				to_read;
	char			buf[101];

	cli_launch_term(self);
	ft_bzero(buf, 101);

	while (ft_strncmp(buf, "\n", 1))
	{
		ioctl(0, FIONREAD, &to_read);
		nbytes = read(0, buf, 100);
		if (!ft_strncmp(buf, "\e", 1))
		{
			handle_up_down(buf);
			if ((!ft_strncmp(buf, "\e[D", 3)) || (!ft_strncmp(buf, "\e[C", 3)))
				continue ;
		}
		else if (!ft_strncmp(buf, "\x7f", 1))
			handle_backspace(self);
		else
		{
			write(1, buf, nbytes);
			if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] == '\n'))
				self->line->append(self->line, buf, nbytes);
		}
	}
	write(1, "\n", 1);
	return (0);
}
