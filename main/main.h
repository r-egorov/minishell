/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:24:45 by cisis             #+#    #+#             */
/*   Updated: 2021/04/20 14:44:48 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <errno.h>
# include <string.h>	// strerror
# include <stdio.h>		// want printf while develop
# include <unistd.h>	// fork

# include "libft.h"
# include "cli.h"
# include "parse.h"
# include "exec.h"

#include <signal.h>
//#include <stdlib.h>

int		catch_signal(int sig, void (*handler)(int));
void	exit_func(int sig);
void	noop_func(int sig);

#endif
