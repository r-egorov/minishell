/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 10:46:18 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/13 12:27:40 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	sigint_handler(int sig)
{
	fprintf(stderr, "sig: %d. Exiting....\n", sig);
	exit(1);
}

void	restore_child_sig()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

void	ignore_parent_sig()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
