/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:24:45 by cisis             #+#    #+#             */
/*   Updated: 2021/04/20 16:54:35 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <errno.h>
# include <string.h>	// strerror
# include <stdio.h>		// want printf while develop
# include <unistd.h>	// fork

# include "minishell.h"
# include "libft.h"
# include "cli.h"
# include "parser.h"
# include "exec.h"

#include <signal.h>
//#include <stdlib.h>

void	sigint_handler(int sig);
void	restore_child_sig();
void	ignore_parent_sig();

//void	noop_func(int sig);

#endif
