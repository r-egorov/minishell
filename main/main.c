/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/20 11:10:36 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main(int argc, char** argv, char **envp)
{
	t_cli	cli;
	t_parse	parse;

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
		//parse_init(&parse, cli.line);
		parse.line = cli.line->str;
		parse.pos = 0;
		//parse.len = cli.len;
		while (parse_next(&parse))
		{
			exec_run(&parse);
		}
		//parse(cli.line);
	}
	cli_del(&cli);
	return (0);
}
