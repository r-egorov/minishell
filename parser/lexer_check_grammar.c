/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_grammar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:22:28 by cisis             #+#    #+#             */
/*   Updated: 2021/05/04 16:02:57 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	lexer_check_sep(t_lexer *self, size_t i)
{
	t_token	*token_prev;

	if (i == 0)
		return (-1);
	token_prev = self->tokens[i - 1];
	if ((token_prev->type == PIPE)
		|| (token_prev->type == SEP)
		|| (token_prev->type == REDIR_IN)
		|| (token_prev->type == REDIR_OUT)
		|| (token_prev->type == REDIR_APPEND))
		return (-1);
	return (0);
}

int	lexer_check_pipe(t_lexer *self, size_t i)
{
	t_token	*token_prev;

	if ((i == 0) || (i == self->tokens_len - 1))
		return (-1);
	token_prev = self->tokens[i - 1];
	if ((token_prev->type == PIPE)
		|| (token_prev->type == SEP))
		return (-1);	
	return(0);
}

int	lexer_check_redir(t_lexer *self, size_t i)
{
	t_token	*token_prev;

	if (i > 0)
	{
		token_prev = self->tokens[i - 1];
		if (token_prev->type == REDIR_IN
			|| token_prev->type == REDIR_OUT
			|| token_prev->type == REDIR_APPEND)
			return (-1);
	}
	return (0);
}

int	lexer_check_grammar(t_lexer *self)
{
	t_token *token_cur;
	size_t	i;
	char	*token_str;

	i = 0;
	while (i < self->tokens_len)
	{
		token_cur = self->tokens[i];
		if (((token_cur->type) == PIPE) && lexer_check_pipe(self, i) == -1)
			return (process_input_error(3));
		if ((token_cur->type == SEP) && lexer_check_sep(self, i) == -1)
			return (process_input_error(4));
		if (((token_cur->type == REDIR_IN)
			|| (token_cur->type == REDIR_OUT)
			|| (token_cur->type == REDIR_APPEND))
			&& (lexer_check_redir(self, i) == -1))
			return (process_input_error(5));
		i++;
	}
	return (0);
}
