/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:23:00 by cisis             #+#    #+#             */
/*   Updated: 2021/04/19 14:03:41 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIST_NODE_H
# define HIST_NODE_H

# include <stdlib.h>
# include "libft.h"
# include "line.h"

typedef struct	s_hnode
{
	t_line		*_hist;
	t_line		*buf;
	int			edited;
	void		(*hist_upd)(struct s_hnode *self, t_line *line);
	void		(*buf_upd)(struct s_hnode *self);
	void		(*del)(struct s_hnode *self);
}				t_hnode;

void	hnode_hist_upd(t_hnode *self, t_line *line);
void	hnode_buf_upd(t_hnode *self);
void	hnode_del(void *hnode);
t_hnode	*hnode_new(void);

#endif
