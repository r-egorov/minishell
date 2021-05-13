/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:21:30 by cisis             #+#    #+#             */
/*   Updated: 2021/05/13 11:37:13 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

static void	handle_arrows(t_cli *self, char *buf)
{
	if (!ft_strncmp(buf, "\e[A", 3))
	{
		if (self->hist_cur->next)
		{
			self->hist_cur = self->hist_cur->next;
			self->line = (t_line *)((t_hnode *)self->hist_cur->content)->buf;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(clr_eos, 1, ft_putchar);
			write(1, self->line->str, self->line->len);
		}
	}
	else if (!ft_strncmp(buf, "\e[B", 3))
	{
		if (self->hist_cur->prev)
		{
			self->hist_cur = self->hist_cur->prev;
			self->line = (t_line *)((t_hnode *)self->hist_cur->content)->buf;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(clr_eos, 1, ft_putchar);
			write(1, self->line->str, self->line->len);
		}
	}
	else if ((!ft_strncmp(buf, "\e[D", 3)) || (!ft_strncmp(buf, "\e[C", 3)))
		return ;
}

static void	handle_tab_backspace(t_cli *self, char *buf)
{
	if (!ft_strncmp(buf, "\t", 1))
		return ;
	else
	{
		if ((self->line->pop_last(self->line)))
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
		}
	}
}

static int	cli_readbuf(t_cli *self, char *buf)
{
	int				nbytes;
	int				to_read;

	while (ft_strncmp(buf, "\n", 1))
	{
		ioctl(0, FIONREAD, &to_read);
		nbytes = read(0, buf, 100);
		if (!ft_strncmp(buf, "\e", 1))
			handle_arrows(self, buf);
		else if ((!ft_strncmp(buf, "\x04", 1)) && (!self->line->str))
			return (0);
		else if (!ft_strncmp(buf, "\x03", 1))
			return (2);
		else if ((!ft_strncmp(buf, "\x7f", 1)) || (!ft_strncmp(buf, "\t", 1)))
			handle_tab_backspace(self, buf);
		else
		{
			write(1, buf, nbytes);
			if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] == '\n'))
				self->line->append(self->line, buf, nbytes);
		}
	}
	return (1);
}

static int	cli_user_input(t_cli *self, char *buf)
{
	int		ret;

	ret = cli_readbuf(self, buf);
	if (ret)
	{
		cli_update_history(self);
		if ((!ft_strcmp(self->line->str, "")) || (ret == 2))
		{
			if (ret == 2)
				write(1, "\n", 1);
			self->hist_cur = self->hist;
			self->hist = self->hist->next;
			ft_dlstdelone(self->hist_cur, hnode_del);
			self->line = NULL;
		}
		return (1);
	}
	return (0);
}

int 	cli_readline(t_cli *self)
{
	char			buf[101];
	int				ret;

	cli_launch_term(self);
	ft_bzero(buf, 101);
	ft_dlstadd_front(&(self->hist), ft_dlstnew(hnode_new()));
	self->hist_cur = self->hist;
	self->line = (t_line *)((t_hnode *)self->hist_cur->content)->buf;
	ret = cli_user_input(self, buf);
	cli_stop_term(self);
	if (ret)
		return (1);
	write(1, "exit\n", 5);
	return (0);
}
