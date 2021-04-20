/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:26:29 by cisis             #+#    #+#             */
/*   Updated: 2021/04/20 16:27:54 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

void	line_del(void *self)
{
	t_line	*obj;

	obj = (t_line *)self;
	if (obj)
	{
		if (obj->str)
		{
			free(obj->str);
			obj->str = NULL;
		}
		free(obj);
		obj = NULL;
	}
}

t_line	*line_new(void)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		process_syserror();
	line->str = NULL;
	line->len = 0;
	line->append = line_append;
	line->pop_last = line_pop_last;
	line->del = line_del;
	return (line);
}
