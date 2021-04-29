/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:30:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/29 15:07:21 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include <stdio.h>
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

#endif
