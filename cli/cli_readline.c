/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:21:30 by cisis             #+#    #+#             */
/*   Updated: 2021/04/15 10:57:08 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include <stdio.h>

static void	line_append(char **original_line, char *src, int nbytes)
{
	char			*tmp;
	char			*line;
	size_t			line_len;

	line = *original_line;
	if (!line)
	{
		src[nbytes] = '\0';
		tmp = (char *)malloc((nbytes + 1) * sizeof(char));
		if (!tmp)
			process_error();
		ft_strlcpy(tmp, src, nbytes + 1);
	}
	else
	{
		line_len = ft_strlen(line);
		tmp = (char *)malloc((line_len + nbytes + 1) * sizeof(char));
		if (!tmp)
			process_error();
		ft_memcpy(tmp, line, line_len + 1);
		ft_strlcat(tmp, src, line_len + nbytes + 1);
		free(line);
	}
	*original_line = tmp;
}

char 	*cli_readline (void)
{
	struct termios	terminal;
	int 			nbytes;
	int				to_read;
	char			buf[2001];
	char			*line;

	line = NULL;
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
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
		}
		else
		{
			write(1, buf, nbytes);
			line_append(&line, buf, nbytes);
		}
	}
	printf("input = |%s|\n", line);
	write(1, "\n", 1);
	return (0);
}

