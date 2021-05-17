/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:30:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/17 13:46:41 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "errors.h"
# include "env.h"
//# include "line.h"

typedef enum e_type
{
	CMD,
	ARG,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_FILE,
	PIPE,
	SEP
}				t_type;

typedef struct s_token
{
	char		*str;
	int			len;
	int			screened;
	t_type		type;

	void		(*append)(struct s_token *self, char *to_append);
	void		(*remove)(struct s_token *self, size_t i);
	void		(*prepare)(struct s_token *self, int exit_status, t_dlist *env);
	void		(*del)(struct s_token *self);
}				t_token;

typedef struct s_lexer
{
	char	*string;
	char	*buf;
	t_token	**tokens;
	size_t	tokens_len;

	void	(*del)(struct s_lexer *self);
	int		(*tokenize)(struct s_lexer *self);
	int		(*check_grammar)(struct s_lexer *self);
}				t_lexer;

typedef struct s_job
{
	char	*cmd;
	char	**argv;
	size_t	argc;
	t_list	*redir_in;
	t_list	*redir_out;
	t_list	*redir_append;

	void	(*del)(struct s_job *self);
}				t_job;

typedef struct s_parser
{
	char	*string;
	t_lexer	*lexer;
	t_job	**jobs;
	t_dlist	*env;
	size_t	jobs_len;
	size_t	pos;
	int		exit_status;

	void	(*del)(struct s_parser *self);
}				t_parser;

void	parser_init(t_parser *self, char *string_to_parse, int exit_status,
			t_dlist *env);
void	parser_del(t_parser *self);
int		parser_next(t_parser *self);
void	parser_refresh(t_parser *self, int exit_status, t_dlist *env);

int		parser_make_jobs(t_parser *self);
t_job	*job_new(void);
void	job_append_arg(t_job *self, char *arg);

t_lexer	*lexer_new(char *string);
void	lexer_del(t_lexer *self);

int		lexer_tokenize(t_lexer *self);
void	lexer_append_token(t_lexer *self, t_token *token);
void	lexer_token_type(t_lexer *self, t_token *token);
t_token	*lexer_get_token(t_lexer *self);
void	lexer_quotes_expandvar(t_lexer *self);
void	lexer_expandvar(t_lexer *self);
void	lexer_insert_varvalue(t_lexer *self, char *var_value);
char	*lexer_get_varname(t_lexer *self);

t_token	*token_new(void);
void	token_del(t_token *self);
void	token_append(t_token *self, char *src);
void	token_prepare(t_token *self, int exit_status, t_dlist *env);

int		is_quotes(char c);
int		is_tokensep(char c);

void	lexer_quotes(t_token *token, char **p_token_end);

int		lexer_check_grammar(t_lexer *self);

#endif
