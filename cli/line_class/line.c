/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:03:36 by cisis             #+#    #+#             */
/*   Updated: 2021/04/20 16:27:09 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

static void	line_stripnl(t_line *self)
{
	char			*nl;

	nl = ft_strchr(self->str, '\n');
	if (nl)
	{
		self->len = nl - self->str;
		*nl = '\0';
	}
}

void	line_append(t_line *self, char *src, int nbytes)
{
	char			*tmp;
	char			*string;

	string = self->str;
	if (!string)
	{
		tmp = (char *)malloc((nbytes + 1) * sizeof(char));
		if (!tmp)
			process_syserror();
		ft_strlcpy(tmp, src, nbytes + 1);
		self->len = nbytes;
	}
	else
	{
		tmp = (char *)malloc((self->len + nbytes + 1) * sizeof(char));
		if (!tmp)
			process_syserror();
		ft_memcpy(tmp, string, self->len + 1);
		ft_strlcat(tmp, src, self->len + nbytes + 1);
		self->len += nbytes;
		free(string);
	}
	self->str = tmp;
	line_stripnl(self);
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

t_line	*line_dup(t_line *line)
{
	t_line	*res;

	res = line_new();
	res->str = ft_strdup(line->str);
	if (!res->str)
		process_syserror();
	res->len = line->len;
	return (res);
}
