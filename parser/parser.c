/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:55:02 by cisis             #+#    #+#             */
/*   Updated: 2021/04/28 13:50:12 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	lexer_del(t_lexer *self)
{
	if (self)
	{
		if (self->string)
			free(self->string);
		free(self);
	}
}

t_lexer	*lexer_new(char *string)
{
	t_lexer *self;

	self = (t_lexer *)malloc(sizeof(t_lexer));
	if (!self)
		process_syserror();
	self->string = ft_strdup(string);
	self->del = lexer_del;
	self->tokens = NULL;
	return (self);
}

void	parser_del(t_parser *self)
{
	if (self)
	{
		free(self->string);
		ft_free_strs(self->argv);
		if (self->lexer)
			self->lexer->del(self->lexer);
	}
}

void	parser_init(t_parser *self, char *string_to_parse)
{
	self->string = string_to_parse;
	self->lexer = NULL;
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
		self->lexer = lexer_new(self->string);
		self->argv = ft_split(self->lexer->string, ' ');
		self->pos = ft_strlen(self->string);
		self->lexer->del(self->lexer);
		return (1);
	}
	return (0);
}
