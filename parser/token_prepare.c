/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prepare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:51:38 by cisis             #+#    #+#             */
/*   Updated: 2021/05/12 17:23:36 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*token_get_varname(t_token *self, size_t i)
{
	char		*string;
	char		*varname;
	char		tmp;

	varname = NULL;
	if (self->str[i + 1])
	{
		string = self->str + i + 1;
		if (ft_isdigit(*string) || *string == '?')
			string++;
		else
		{
			while (ft_isalnum(*string) || *string == '_')
				string++;
		}
		tmp = *string;
		*string = '\0';
		varname = ft_strdup(self->str + i + 1);
		if (!varname)
			process_syserror();
		*string = tmp;
	}
	return (varname);
}

void	token_insert_varvalue(t_token *self, size_t *index, char *varvalue,
		char *varname)
{
	char		*tmp1;
	char		*tmp2;
	size_t		i;

	i = *index;
	self->str[i] = '\0';
	i++;
	tmp1 = ft_strjoin(self->str, varvalue);
	if (!tmp1)
		process_syserror();
	i += ft_strlen(varname);
	tmp2 = ft_strjoin(tmp1, self->str + i);
	if (!tmp2)
		process_syserror();
	free(tmp1);
	free(self->str);
	self->str = tmp2;
	self->len = ft_strlen(tmp2);
}

void	token_expandvar(t_token *self, size_t *i)
{
	char		*varname;
	char		*varvalue;

	varname = token_get_varname(self, *i);
	if (ft_isdigit(*varname))
	{
		if (!ft_strcmp(varname, "0"))
			varvalue = "minihell";
		else
			varvalue = "";
	}
	else
		varvalue = getenv(varname);
	token_insert_varvalue(self, i, varvalue, varname);
	free(varname);
	*i += ft_strlen(varvalue);
}

void	token_prepare(t_token *self)
{
	size_t		i;

	i = 0;
	while (self->str[i])
	{
		if (self->str[i] == '\\')
		{
			self->remove(self, i);
			i++;
		}
		else if (self->str[i] == '$')
			token_expandvar(self, &i);
		else if (self->str[i] == '\'')
		{
			self->remove(self, i);
			while (self->str[i] != '\'')
				i++;
			self->remove(self, i);
		}
		else if (self->str[i] == '\"')
		{
			//printf("HERE\n");
			self->remove(self, i);
			while (self->str[i] != '\"')
			{
			//	printf("|%c|\n", self->str[i]);
				if ((self->str[i] == '\\')
						&& (self->str[i + 1] == '\\'
							|| self->str[i + 1] == '$'
							|| self->str[i + 1] == '\"'))
				{
			//		printf("REMOVING |%c|\n", self->str[i]);
					self->remove(self, i);
					i++;
				}
				else if (self->str[i] == '$')
					token_expandvar(self, &i);
				else
					i++;
			}
			self->remove(self, i);

		}
		else
			i++;
	}
}
