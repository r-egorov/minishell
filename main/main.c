/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/20 16:56:02 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main(int argc, char** argv, char **envp)
{
	t_cli	cli;
	t_parser	parser;

	cli_init(&cli);

	(void)argc;
	(void)argv;
	(void)envp;

	catch_signal(SIGINT, exit_func);
	catch_signal(SIGQUIT, noop_func);

	while (cli_readline(&cli))
	{
		printf("input = |%s|\nlen = %d\n", cli.line->str, cli.line->len);
		printf("in list = |%s|\n", (((t_line *)cli.hist->content)->str));
		if (cli.line->len == 0)
			break ;
		parser_init(&parser, cli.line->str);
		while (parser_next(&parser))
		{
			exec_run(&parser);
		}
	}
	cli_del(&cli);
	return (0);
}
