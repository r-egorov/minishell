/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 11:42:18 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main(int argc, char** argv, char **envp)
{
	t_cli	cli;
	t_parser	parser;
	t_exec	ex;

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
			exec_init(&parser, &ex);
			exec_run(&ex);
		}
	}
	cli_del(&cli);
	return (0);
}
