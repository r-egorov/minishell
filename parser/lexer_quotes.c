/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 16:16:24 by cisis             #+#    #+#             */
/*   Updated: 2021/05/12 17:31:40 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	lexer_quotes(t_token *token, char **p_token_end)
{
	char	*token_end;

	token_end = *p_token_end;
	token->append(token, token_end);
	if (*token_end++ == '\'')
	{
		while (*token_end && *token_end != '\'')
			token->append(token, token_end++);
	}
	else
	{
		while (*token_end && *token_end != '\"')
		{
			 if (*token_end == '\\')
				 token->append(token, token_end++);
			 token->append(token, token_end++);
		}
	}
	if (*token_end)
		token->append(token, token_end);
	*p_token_end = token_end;
}
