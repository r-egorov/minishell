/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:55:02 by cisis             #+#    #+#             */
/*   Updated: 2021/04/30 16:49:48 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	printtokens(t_token **tokens, size_t len)
{
	size_t i = 0;

	while (i < len)
	{
		printf("str|%s|\t\t\t\tlen|%d|\tscrnd|%d|\n", (tokens[i])->str, (tokens[i])->len, (tokens[i])->screened);
		i++;
	}
}

int	parser_next(t_parser *self)
{
	if (self->pos < ft_strlen(self->string)) // should be if (!self->lexer->tokens)
	{
		self->lexer = lexer_new(self->string);
		if (self->lexer->tokenize(self->lexer) == -1)
		{
			self->lexer->del(self->lexer);
			return (0);
		}
		//printtokens(self->lexer->tokens, self->lexer->tokens_len); //FIXME
		//printf("ntok %zu\n", self->lexer->tokens_len);
		self->argv = ft_split(self->string, ' ');
		self->pos = ft_strlen(self->string);
		self->lexer->del(self->lexer); 
		return (1);
	}
	return (0);
}
