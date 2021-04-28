/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:55:02 by cisis             #+#    #+#             */
/*   Updated: 2021/04/28 13:16:49 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	parser_del(t_parser *self)
{
	if (self)
	{
		free(self->string);
		ft_free_strs(self->argv);
	}
}

void	parser_init(t_parser *self, char *string_to_parse)
{
	self->string = ft_strdup(string_to_parse);
	self->pos = 0;
	self->exec = NULL;
	self->argv = NULL;
	self->pipe = 0;
	self->redir_out = 0;
	self->redir_in = 0;
	self->del = parser_del;
}

int	parser_next(t_parser *self)
{
	if (self->pos < ft_strlen(self->string))
	{
		printf("[parse next] got line: %s\n", self->string);
		self->exec = ft_strdup(self->string);
		self->argv = ft_split(self->string, ' ');
		self->pos = ft_strlen(self->exec);
		return (1);
	}
	return (0);
}
