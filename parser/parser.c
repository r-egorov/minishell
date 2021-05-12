/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:55:02 by cisis             #+#    #+#             */
/*   Updated: 2021/05/12 14:17:49 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_del(t_parser *self)
{
	size_t	i;

	i = 0;
	if (self)
	{
		free(self->string);
		self->string = NULL;
		if (self->lexer)
		{
			self->lexer->del(self->lexer);
			self->lexer = NULL;
		}
		if (self->jobs)
		{
			while (self->jobs[i])
			{
				(self->jobs[i])->del(self->jobs[i]);
				self->jobs[i] = NULL;
				i++;
			}
			self->jobs = NULL;
		}
	}
}

void	parser_clean(t_parser *self)
{
	size_t	i;

	i = 0;
	if (self)
	{
		if (self->jobs)
		{
			while (i < self->jobs_len)
			{
				(self->jobs[i])->del(self->jobs[i]);
				self->jobs[i] = NULL;
				i++;
			}
			free(self->jobs);
			self->jobs = NULL;
			self->jobs_len = 0;
		}
	}
}

void	parser_init(t_parser *self, char *string_to_parse)
{
	self->string = string_to_parse;
	self->lexer = NULL;
	self->jobs = NULL;
	self->jobs_len = 0;
	self->pos = 0;
	self->del = parser_del;
}

#include <stdio.h>
int		print_tokens(t_lexer *lexer)
{
	size_t 	i = 0;
	t_token	*token;

	printf("=======TOKENS=====\n");
	while (i < lexer->tokens_len)
	{
		token = lexer->tokens[i];
		printf("str |%s| len |%d| type |%d|\n", token->str, token->len, token->type);
		i++;
	}
	printf("============\n");
	return (0);
}

int	parser_next(t_parser *self)
{
	if (!self->lexer)
	{
		self->lexer = lexer_new(self->string);
		if ((self->lexer->tokenize(self->lexer) == -1)
			|| self->lexer->check_grammar(self->lexer) == -1)
		{
			self->lexer->del(self->lexer);
			return (0);
		}
		print_tokens(self->lexer);
	}
	if (self->pos < self->lexer->tokens_len)
	{
		parser_make_jobs(self);
		return (1);
	}
	else
	{
		self->lexer->del(self->lexer);
		return (0);
	}
}
