/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:30:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/18 14:29:35 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include <stdio.h>
//# include "line.h"

typedef struct	s_parse {
	char	*line;
	size_t	pos;
//	int		len;
	char	*exec;
}				t_parse;

int		parse_init(t_parse *e);
int		parse_next(t_parse *e);

#endif
