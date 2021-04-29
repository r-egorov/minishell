/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 18:06:59 by cisis             #+#    #+#             */
/*   Updated: 2021/04/29 18:07:00 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_token	*lexer_get_token(t_lexer *self)
{
	t_token	*token;
	char	*token_end;

	lexer_expandvar(self);
	token = token_new();
	token_end = self->buf;
	
	while (*token_end && *token_end != ' ' && !is_tokensep(*token_end))
	{
		if (*token_end == '\\')
		{
			token_end++;
			token->append(token, token_end);
			token_end++;
			token->screened = 1;
		}
		else if (is_quotes(*token_end))
		{
			if (*token_end == '\'')
			{
				token_end++;
				while (*token_end && *token_end != '\'')
				{
					token->append(token, token_end);
					token_end++;
				}
			}
			else
			{
				token_end++;
				self->buf = token_end;
				lexer_quotes_expandvar(self);
				token_end = self->buf;
				while ((*token_end) && (*token_end != '\"'))
				{
					if (*token_end == '\\')
					{
						if ((*(token_end + 1) == '\"') ||
							(*(token_end + 1) == '$'))
							token_end++;
					}
					token->append(token, token_end);
					token_end++;
				}
			}
			if (!*token_end)
				process_error(); // NO MATCHING QUOTE
			token_end++;
		}
		else
		{
			token->append(token, token_end);
			token_end++;
		}
	}
	
	if (is_tokensep(*token_end) && is_tokensep(*self->buf))
	{
		token->append(token, token_end);
		if (*token_end == '>')
		{
			if ((*token_end + 1) && ((*(token_end + 1)) == '>'))
			{
				token_end++;
				token_append(token, token_end);
			}
			else if ((*token_end + 1) && ((*token_end + 1) == '<'))
				process_error(); // UNEXPECTED TOKEN  `><`
		}
		token_end++;
	}

	// QUOTES handling	

	if (*token_end == ' ')
		self->buf = token_end + 1;
	else
		self->buf = token_end;
	return (token);
}