/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expandvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 18:02:33 by cisis             #+#    #+#             */
/*   Updated: 2021/04/30 16:48:24 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*lexer_get_varname(t_lexer *self)
{
	char	*string;
	char	*varname;
	char	tmp;

	varname = NULL;
	if (self->buf + 1)
	{
		string = self->buf + 1;
		while (ft_isalpha(*string))
			string++;
		tmp = *string;
		*string = '\0';
		varname = ft_strdup(self->buf + 1);
		if (!varname)
			process_syserror();
		*string = tmp;
	}
	return (varname);
}

void	lexer_insert_varvalue(t_lexer *self, char *var_value)
{
	char	*tmp1;
	char	*tmp2;
	size_t	position;

	position = self->buf - self->string;
	*self->buf = '\0';
	self->buf++;
	tmp1 = ft_strjoin(self->string, var_value);
	if (!tmp1)
		process_syserror();
	while (ft_isalpha(*self->buf))
		self->buf++;
	tmp2 = ft_strjoin(tmp1, self->buf);
	if (!tmp2)
		process_syserror();
	free(tmp1);
	free(self->string);
	self->string = tmp2;
	self->buf = self->string + position;
}

void	lexer_expansion_exec(t_lexer *self)
{
	char	*var_name;
	char	*var_value;

	var_name = lexer_get_varname(self);
	var_value = getenv(var_name);
	free(var_name);
	lexer_insert_varvalue(self, var_value);
}

void	lexer_expandvar(t_lexer *self)
{
	size_t	position;

	position = self->buf - self->string;
	while (*self->buf && *self->buf != ' ' && !is_tokensep(*self->buf)
		&& !is_quotes(*self->buf))
	{
		if ((*self->buf == '$') && (ft_isalpha(*(self->buf + 1))))
		{
			if ((self->buf - self->string) && (*(self->buf - 1) == '\\'))
			{
				self->buf++;
				continue ;
			}
			else
				lexer_expansion_exec(self);
		}
		self->buf++;
	}
	self->buf = self->string + position;
}

void	lexer_quotes_expandvar(t_lexer *self)
{
	size_t	position;

	position = self->buf - self->string;
	while ((*self->buf) && (*self->buf != '\"'))
	{
		if ((*self->buf == '$') && (ft_isalpha(*(self->buf + 1))))
		{
			if ((self->buf - self->string) && (*(self->buf - 1) == '\\'))
			{
				self->buf++;
				continue ;
			}
			else
				lexer_expansion_exec(self);
		}
		if (*self->buf != '\"')
			self->buf++;
	}
	self->buf = self->string + position;
}
