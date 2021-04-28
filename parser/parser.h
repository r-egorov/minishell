/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:30:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/28 16:54:30 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include <stdio.h>
//# include "line.h"

typedef struct s_lexer
{
	char	*string;
	char	*buf;
	char	**tokens;
	size_t	tokens_len;

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

typedef struct s_token
{
	char		*str;
	int			len;
	void		(*append)(struct s_line *self, char *to_append, int size);
	void		(*del)(void *self);
}				t_token;

void	parser_init(t_parser *self, char *string_to_parse);
void	parser_del(t_parser *self);
int		parser_next(t_parser *self);

#endif
