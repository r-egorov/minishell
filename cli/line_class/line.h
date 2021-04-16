/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:02:59 by cisis             #+#    #+#             */
/*   Updated: 2021/04/16 16:01:22 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include <stdlib.h>
# include "libft.h"
# include "errors.h"

/*
 * A `line` class containing a string which was entered (or copied) into stdin
 * by the user. The string and its length are modified dynamically during the
 * input.
 *
 * Fields:
 * 	char	*str - a pointer to the string itself
 * 	int		len - the length of the string
 *
 * Methods:
 * 	void	append(self, char *to_append, int size) - appends N (N == size)
 * 	chars from the to_append buffer
 *
 * 	char	line_pop_last(self) - removes and returns the last char in the
 * 	string. If there was only one char in the string, frees the pointer 
 *	self->str
*/

typedef struct s_line
{
	char		*str;
	int			len;
	void		(*append)(struct s_line *self, char *to_append, int size);
	char		(*pop_last)(struct s_line *self);
	void		(*del)(void *self);
}				t_line;

t_line	*line_new(void);
void	line_del(void *self);
char	line_pop_last(t_line *self);
void	line_append(t_line *self, char *src, int nbytes);
t_line	*line_dup(t_line *line);

#endif
