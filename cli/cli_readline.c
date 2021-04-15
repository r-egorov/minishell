/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:21:30 by cisis             #+#    #+#             */
/*   Updated: 2021/04/15 13:11:17 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include <stdio.h>

char 	*cli_readline (void)
{
	struct termios	terminal;
	int 			nbytes;
	int				to_read;
	char			buf[2001];
	t_line			*line;


	line = line_new();
	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~(ECHO);
	terminal.c_lflag &= ~(ICANON);

	if (tcsetattr(0, TCSANOW, &terminal) == -1)
		process_error();

	if (tgetent(0, "xterm-256color") == -1)
		process_error();

	write(1, "minihell > ", 11);

	ft_bzero(buf, 2001);
	tputs(save_cursor, 1, ft_putchar);

	while (ft_strncmp(buf, "\n", 1))
	{
		ioctl(0, FIONREAD, &to_read);
		nbytes = read(0, buf, 10);
		if (!ft_strncmp(buf, "\e", 1))
		{
			if (!ft_strcmp(buf, "\e[A"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(clr_eos, 1, ft_putchar);
				write(1, "UP", 2);
			}
			else if (!ft_strcmp(buf, "\e[B"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(clr_eos, 1, ft_putchar);
				write(1, "DOWN", 4);
			}
			else if ((!ft_strcmp(buf, "\e[D")) || (!ft_strcmp(buf, "\e[C")))
				continue ;
		}
		else if (!ft_strncmp(buf, "\x7f", 1))
		{
			if ((line->pop_last(line)))
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(delete_character, 1, ft_putchar);
			}
		}
		else
		{
			write(1, buf, nbytes);
			if (buf[0] >= 32 && buf[0] <= 126)
				line->append(line, buf, nbytes);
		}
	}
	printf("input = |%s|\nlen = %d\n", line->str, line->len);
	write(1, "\n", 1);
	return (0);
}
