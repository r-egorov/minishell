/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:30:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/29 18:10:19 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "errors.h"
//# include "line.h"

typedef struct s_token
{
	char		*str;
	int			len;
	int			screened;
	void		(*append)(struct s_token *self, char *to_append);
	void		(*del)(struct s_token *self);
}				t_token;

typedef struct s_lexer
{
	char	*string;
	char	*buf;
	t_token	**tokens;
	size_t	tokens_len;
	int		quotes;

	void	(*del)(struct s_lexer *self);
	void	(*tokenize)(struct s_lexer *self);
}				t_lexer;

typedef struct s_parser
{
	char	*string;
	t_lexer	*lexer;
	size_t	pos;
	char	*exec;
	char	**argv;
	t_btree	*ast;
	int		pipe;
	int		redir_out;
	int		redir_in;
	
	void	(*del)(struct s_parser *self);
}				t_parser;

void	parser_init(t_parser *self, char *string_to_parse);
void	parser_del(t_parser *self);
int		parser_next(t_parser *self);

t_lexer	*lexer_new(char *string);
void	lexer_del(t_lexer *self);

void	lexer_tokenize(t_lexer *self);
void	lexer_append_token(t_lexer *self, t_token *token);
t_token	*lexer_get_token(t_lexer *self);
void	lexer_quotes_expandvar(t_lexer *self);
void	lexer_expandvar(t_lexer *self);
void	lexer_insert_varvalue(t_lexer *self, char *var_value);
char	*lexer_get_varname(t_lexer *self);

t_token	*token_new(void);
void	token_del(t_token *self);
void	token_append(t_token *self, char *src);

int		is_quotes(char c);
int		is_tokensep(char c);

#endif
