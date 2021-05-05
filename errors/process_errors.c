/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:07:07 by cisis             #+#    #+#             */
/*   Updated: 2021/05/04 16:04:07 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void 	process_syserror()
{
	char 	*msg;

	msg = strerror(errno);
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));

	exit(errno);
}

void 	process_error()
{
	char 	*msg;

	msg = strerror(errno);
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
}

int	process_input_error(size_t errcode)
{
	char 	*msg[50];

	msg[1] = "No matching quote\n";
	msg[2] = "syntax error near unexpected token `<`\n";
	msg[3] = "syntax error near unexpected token `|`\n";
	msg[4] = "syntax error near unexpected token `;`\n";
	msg[5] = "syntax error near the redirect token\n";
	write(2, "minihell: ", 10);
	write(2, msg[errcode], ft_strlen(msg[errcode]));
	return (-1);
}
