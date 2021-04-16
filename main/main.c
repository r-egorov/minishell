/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/16 16:24:15 by cisis            ###   ########.fr       */
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

	while (cli_readline(&cli))
	{
		printf("input = |%s|\nlen = %d\n", cli.line->str, cli.line->len);
		printf("in list = |%s|\n", (((t_line *)cli.hist->content)->str));
		if (cli.line->len == 0)
			break ;
	}
	cli_del(&cli);
	return (0);
}
