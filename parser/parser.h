/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:30:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/28 13:16:31 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include <stdio.h>
//# include "line.h"

typedef struct s_parser
{
	char	*string;
	size_t	pos;
	char	*exec;
	char	**argv;
	t_btree	*ast;
	int		pipe;
	int		redir_out;
	int		redir_in;
	
	void	(*del)(struct s_parser *self);
}				t_parser;

void	parser_init(t_parser *self, char *string_to_parse);
void	parser_del(t_parser *self);
int		parser_next(t_parser *self);

#endif
