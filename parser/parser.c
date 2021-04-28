/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:55:02 by cisis             #+#    #+#             */
/*   Updated: 2021/04/28 15:47:08 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	lexer_del(t_lexer *self)
{
	if (self)
	{
		if (self->string)
			free(self->string);
		if (self->tokens)
			ft_free_strs(self->tokens);
		free(self);
	}
}

char	*get_token(char **original_string)
{
	char		*token;
	char		*string;
	char		*string_start;

	string = *original_string;
	string_start = string;
	while (*string && *string != ' ')
		string++;
	if (*string == ' ')
		*original_string = string + 1;
	else
		*original_string = string;
	*string = '\0';
	token = ft_strdup(string_start);
	if (!token)
		process_syserror();
	return (token);
}

void	lexer_append_token(t_lexer *self, char *token)
{
	char 	**tmp;
	size_t	i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (self->tokens_len + 2));
	if (!tmp)
		process_syserror();
	if (self->tokens_len == 0)
	{
		tmp[0] = token;
		tmp[1] = NULL;
	}
	else
	{
		while (self->tokens[i])
		{
			tmp[i] = self->tokens[i];
			i++;
		}
		tmp[i] = token;
		tmp[++i] = NULL;
		free(self->tokens);
	}
	self->tokens = tmp;
	self->tokens_len += 1;
}

void	lexer_tokenize(t_lexer *self)
{
	size_t		i;
	char		*token;
	char		*string_to_parse;

	i = 0;
	string_to_parse = self->string;
	while (*string_to_parse)
	{
		while (*string_to_parse == ' ')
			string_to_parse++;
		token = get_token(&string_to_parse);
		lexer_append_token(self, token);
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
	self->tokens_len = 0;
	self->tokenize = lexer_tokenize;
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


void	printstrs(char **strs)
{
	int i = 0;

	while (strs[i])
	{
		printf("|%s|\n", strs[i]);
		i++;
	}
}

int	parser_next(t_parser *self)
{
	if (self->pos < ft_strlen(self->string)) // should be if (!self->lexer->tokens)
	{
		self->lexer = lexer_new(self->string);
		self->lexer->tokenize(self->lexer);
		printstrs(self->lexer->tokens); //FIXME
		self->argv = ft_split(self->lexer->string, ' ');
		self->pos = ft_strlen(self->string);
		self->lexer->del(self->lexer); 
		return (1);
	}
	return (0);
}
