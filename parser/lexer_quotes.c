/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 16:16:24 by cisis             #+#    #+#             */
/*   Updated: 2021/05/12 14:26:38 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
static void	lexer_single_quote(t_token *token, char **p_token_end)
{
	char	*token_end;

	token_end = *p_token_end;
	while (*token_end && *token_end != '\'')
	{
		token->append(token, token_end);
		token_end++;
	}
	*p_token_end = token_end;
}

static void	lexer_double_quote(t_lexer *self, t_token *token,
		char **p_token_end)
{
	char	*token_end;

	token_end = *p_token_end;
	self->buf = token_end;
	lexer_quotes_expandvar(self);
	token_end = self->buf;
	while ((*token_end) && (*token_end != '\"'))
	{
		if (*token_end == '\\')
		{
			if ((*(token_end + 1) == '\"') || (*(token_end + 1) == '$'))
				token_end++;
		}
		token->append(token, token_end);
		token_end++;
	}
	*p_token_end = token_end;
}
*/

void	lexer_quotes(t_token *token, char **p_token_end)
{
	char	*token_end;
	char	matching_quote;

	token_end = *p_token_end;
	matching_quote = *token_end;
	token->append(token, token_end++);
	while (*token_end && *token_end != matching_quote)
		token->append(token, token_end++);
	if (*token_end)
		token->append(token, token_end);
	*p_token_end = token_end;
}
