/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:29:30 by cisis             #+#    #+#             */
/*   Updated: 2021/04/20 16:29:14 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hist_node.h"

void	hnode_hist_upd(t_hnode *self, t_line *line)
{
	if (self->_hist)
		self->_hist->del(self->_hist);
	self->_hist = line_dup(line);
}

void	hnode_buf_upd(void *obj)
{
	t_hnode	*self;

	self = (t_hnode *)obj;
	if (self->_hist)
	{
		if (self->buf)
			self->buf->del(self->buf);
		self->buf = line_dup(self->_hist);
	}
}

void	hnode_del(void *hnode)
{
	t_hnode		*self;

	self = (t_hnode *)hnode;
	if (self)
	{
		if (self->_hist)
			self->_hist->del(self->_hist);
		if (self->buf)
			self->buf->del(self->buf);
		self->_hist = NULL;
		self->buf = NULL;
		free(self);
		self = NULL;
	}
}

t_hnode	*hnode_new(void)
{
	t_hnode		*self;

	self = (t_hnode *)malloc(sizeof(t_hnode));
	if (!self)
		process_syserror();
	self->_hist = line_new();
	self->buf = line_new();
	self->hist_upd = hnode_hist_upd;
	self->buf_upd = hnode_buf_upd;
	self->del = hnode_del;
	return (self);
}
