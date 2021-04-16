/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/16 13:54:09 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int		main(int argc, char** argv, char **envp)
{
	t_cli	cli;

	cli_init(&cli);

	(void)argc;
	(void)argv;
	(void)envp;

	cli_readline(&cli);
	printf("input = |%s|\nlen = %d\n", cli.line->str, cli.line->len);
	return (0);
}
