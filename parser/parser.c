/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:55:02 by cisis             #+#    #+#             */
/*   Updated: 2021/04/28 18:36:43 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		is_tokensep(char c)
{
	if (c == '>' ||
		c == '<' ||
		c == '|' ||
		c == ';')
		return (1);
	return (0);
}

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

char	*lexer_get_varname(t_lexer *self)
{
	char	*string;
	char	*varname;
	char	tmp;

	varname = NULL;
	if (self->buf + 1)
	{
		string = self->buf + 1;
		while (ft_isalpha(*string))
			string++;
		tmp = *string;
		*string = '\0';
		varname = ft_strdup(self->buf + 1);
		if (!varname)
			process_syserror();
		*string = tmp;
	}
	return (varname);
}

void	lexer_insert_varvalue(t_lexer *self, char *var_value)
{
	char	*tmp1;
	char	*tmp2;
	size_t	position;

	position = self->buf - self->string;
	*self->buf = '\0';
	self->buf++;
	tmp1 = ft_strjoin(self->string, var_value);
	if (!tmp1)
		process_syserror();
	while (ft_isalpha(*self->buf))
		self->buf++;
	tmp2 = ft_strjoin(tmp1, self->buf);
	if (!tmp2)
		process_syserror();
	free(tmp1);
	free(self->string);
	self->string = tmp2;
	self->buf = self->string + position;
}

void	lexer_expandvar(t_lexer *self)
{
	char 	*var_name;
	char	*var_value;
	size_t	position;

	position = self->buf - self->string;
	while (*self->buf && *self->buf != ' ' && !is_tokensep(*self->buf))
	{
		if ((*self->buf == '$') && (ft_isalpha(*(self->buf + 1))))
		{
			var_name = lexer_get_varname(self);
			var_value = getenv(var_name);
			free(var_name);
			lexer_insert_varvalue(self, var_value);
		}
		self->buf++;
	}
	self->buf = self->string + position;
}

void	check_sep(char **ext_string)
{
	char 	*string;

	string = *ext_string;
	if (*string == '>')
	{
		if ((*string + 1) && ((*(string + 1)) == '>'))
			string++;
		else if ((*string + 1) && ((*string + 1) == '<'))
			process_error(); // UNEXPECTED TOKEN  `><`
	}
	string++;
	*ext_string = string;
			
}

char	*lexer_get_token(t_lexer *self)
{
	char		*token;
	char		*string;
	char		*string_start;
	char		tmp;

	lexer_expandvar(self);
	while (*self->buf == ' ')
		self->buf++;
	printf("string %s\nbuf %s\n", self->string, self->buf);
	string = self->buf;
	string_start = self->buf;
	while (*string && *string != ' ' && !is_tokensep(*string))
		string++;

	if (is_tokensep(*string) && is_tokensep(*self->buf))
		check_sep(&string);

	if (*string == ' ')
		self->buf = string + 1;
	else
		self->buf = string;

	tmp = *string;
	*string = '\0';
	token = ft_strdup(string_start);
	if (!token)
		process_syserror();
	*string = tmp;
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

	i = 0;
	while (*self->buf)
	{
		while (*self->buf == ' ')
			self->buf++;
		token = lexer_get_token(self);
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
	self->buf = self->string;
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
		printf("ntok %zu\n", self->lexer->tokens_len);
		self->argv = ft_split(self->lexer->string, ' ');
		self->pos = ft_strlen(self->string);
		self->lexer->del(self->lexer); 
		return (1);
	}
	return (0);
}
