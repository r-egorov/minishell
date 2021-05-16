/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:43:37 by cisis             #+#    #+#             */
/*   Updated: 2021/05/16 18:30:08 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

void	process_syserror(void);
void	process_error(void);
int		process_input_error(size_t errcode);
int		perr(char *cmd, char *arg, char *err, int code);

#endif
