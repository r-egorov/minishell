/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:02:59 by cisis             #+#    #+#             */
/*   Updated: 2021/04/15 13:09:20 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include <stdlib.h>
# include "main.h"
# include "libft.h"

typedef struct	s_line
{
	char		*str;
	int			len;
	void		(*append)(struct s_line *self, char *to_append, int size);
	char		(*pop_last)(struct s_line *self);
	void		(*del)(struct s_line *self);
}				t_line;

t_line	*line_new(void);
void	line_del(t_line *self);
char	line_pop_last(t_line *self);
void	line_append(t_line *self, char *src, int nbytes);

#endif
