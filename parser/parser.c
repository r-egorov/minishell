/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:55:02 by cisis             #+#    #+#             */
/*   Updated: 2021/04/20 17:05:49 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	parser_init(t_parser *self, char *string_to_parse)
{
	self->line = string_to_parse;
	self->pos = 0;
	self->exec = NULL;
	self->argv = NULL;
	self->pipe = 0;
	self->redir_out = 0;
	self->redir_in = 0;
}

int	parser_next(t_parser *e)
{
	if (e->pos < ft_strlen(e->line))
	{
		printf("[parse next] got line: %s\n", e->line);
		e->exec = ft_strdup(e->line);
		e->pos = ft_strlen(e->exec);
		return (1);
	}
	return (0);
}
