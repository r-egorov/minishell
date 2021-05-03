/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:54:31 by cisis             #+#    #+#             */
/*   Updated: 2021/04/29 17:54:31 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	token_append(t_token *self, char *src)
{
	char			*tmp;
	char			*string;

	string = self->str;
	tmp = (char *)malloc((self->len + 2) * sizeof(char));
	if (!tmp)
		process_syserror();
	if (!string)
	{
		ft_strlcpy(tmp, src, 2);
		self->len = 1;
	}
	else
	{
		ft_strlcpy(tmp, string, self->len + 1);
		ft_strlcat(tmp, src, self->len + 2);
		self->len += 1;
		free(string);
	}
	self->str = tmp;
}

void	token_del(t_token *self)
{
	if (self)
	{
		if (self->str)
		{
			free(self->str);
			self->str = NULL;
		}
		free(self);
		self = NULL;
	}
}

t_token	*token_new(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		process_syserror();
	token->str = NULL;
	token->len = 0;
	token->screened = 0;
	token->append = token_append;
	token->del = token_del;
	return (token);
}