/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:22:04 by cisis             #+#    #+#             */
/*   Updated: 2021/04/20 16:25:03 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

void	cli_init(t_cli *self)
{
	self->hist = NULL;
	self->hist_cur = NULL;
	self->readline = cli_readline;
	self->line = NULL;
}

void	cli_del(t_cli *self)
{
	ft_dlstclear(&(self->hist), hnode_del);
}

void	cli_launch_term(t_cli *self)
{
	tcgetattr(0, &(self->term));
	self->term.c_lflag &= ~(ECHO);
	self->term.c_lflag &= ~(ICANON);
	if (tcsetattr(0, TCSANOW, &self->term) == -1)
		process_syserror();
	if (tgetent(0, "xterm-256color") == -1)
		process_syserror();
	write(1, "minihell > ", 11);
	tputs(save_cursor, 1, ft_putchar);
}
