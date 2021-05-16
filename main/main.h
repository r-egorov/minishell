/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:24:45 by cisis             #+#    #+#             */
/*   Updated: 2021/05/16 18:34:58 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <errno.h>
# include <string.h>	// strerror
# include <stdio.h>		// printf
# include <unistd.h>	// fork
# include <signal.h>

# include "minishell.h"
# include "libft.h"
# include "cli.h"
# include "parser.h"
# include "exec.h"

void	sigint_handler(int sig);
void	restore_child_sig(void);
void	ignore_parent_sig(void);

#endif
