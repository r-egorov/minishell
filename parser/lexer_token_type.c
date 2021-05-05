/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:23:09 by cisis             #+#    #+#             */
/*   Updated: 2021/05/05 17:05:44 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	lexer_previous_type(t_lexer *self, t_token *token)
{
	size_t	len;

	len = self->tokens_len;
	if (len == 0)
		token->type = CMD;
	else if ((self->tokens[len - 1])->type == CMD
		|| (self->tokens[len - 1])->type == ARG)
		token->type = ARG;
	else if ((self->tokens[len - 1])->type == REDIR_OUT
		|| (self->tokens[len - 1])->type == REDIR_IN
		|| (self->tokens[len - 1])->type == REDIR_APPEND)
		token->type = REDIR_FILE;
	else if ((self->tokens[len - 1])->type == PIPE
		|| (self->tokens[len - 1])->type == SEP)
		token->type = CMD;
	else
		token->type = CMD;
}

void	lexer_token_type(t_lexer *self, t_token *token)
{
	char	*token_str;

	token_str = token->str;
	if (!ft_strcmp(token_str, "|") && !token->screened)
		token->type = PIPE;
	else if (!ft_strcmp(token_str, ";") && !token->screened)
		token->type = SEP;
	else if (!ft_strcmp(token_str, ">") && !token->screened)
		token->type = REDIR_OUT;
	else if (!ft_strcmp(token_str, ">>") && !token->screened)
		token->type = REDIR_APPEND;
	else if (!ft_strcmp(token_str, "<") && !token->screened)
		token->type = REDIR_IN;
	else
		lexer_previous_type(self, token);
}
