/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:21:30 by cisis             #+#    #+#             */
/*   Updated: 2021/04/15 12:48:54 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"
#include <stdio.h>

void	line_append(t_line *self, char *src, int nbytes)
{
	char			*tmp;
	char			*string;

	string = self->str;
	if (!string)
	{
		tmp = (char *)malloc((nbytes + 1) * sizeof(char));
		if (!tmp)
			process_error();
		ft_strlcpy(tmp, src, nbytes + 1);
		self->len = nbytes;
	}
	else
	{
		tmp = (char *)malloc((self->len + nbytes + 1) * sizeof(char));
		if (!tmp)
			process_error();
		ft_memcpy(tmp, string, self->len + 1);
		ft_strlcat(tmp, src, self->len + nbytes + 1);
		self->len += nbytes;
		free(string);
	}
	self->str = tmp;
}

char	line_pop_last(t_line *self)
{
	char	res;

	if (self->len >= 1)
	{
		if (self->len == 1)
		{
			res = self->str[0];
			free(self->str);
			self->str = NULL;
			self->len = 0;
		}
		else
		{
			res = self->str[self->len - 1];
			self->str[self->len - 1] = '\0';
			self->len -= 1;
		}
		return (res);
	}
	return (0);
}

void	line_del(t_line *self)
{
	if (self->str)
		free(self->str);
	free(self);
}

t_line	*line_new(void)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		process_error();
	line->str = NULL;
	line->len = 0;
	line->append = line_append;
	line->pop_last = line_pop_last;
	line->del = line_del;
	return (line);
}

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
			if (buf[0] >= 33 && buf[0] <= 126)
				line->append(line, buf, nbytes);
		}
	}
	printf("input = |%s|\nlen = %d\n", line->str, line->len);
	write(1, "\n", 1);
	return (0);
}
