/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 10:46:18 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/20 10:55:09 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exit_func(int sig)
{

	printf("sig: %d. Exiting....\n", sig);
	exit (1);
}

int	catch_signal(int sig, void (*handler)(int))
{
	struct sigaction action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return (sigaction(sig, &action, 0));
}