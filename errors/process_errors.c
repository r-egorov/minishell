/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:07:07 by cisis             #+#    #+#             */
/*   Updated: 2021/04/16 16:28:02 by cisis            ###   ########.fr       */
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
