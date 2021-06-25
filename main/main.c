/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/17 13:47:10 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	minishell_init(t_exec *e)
{
	extern char	**environ;
	int			i;

	ft_bzero(e, sizeof(*e));
	i = 0;
	while (environ[i])
	{
		put_env(&e->env, environ[i]);
		i++;
	}
	update_pwd(e);
	return (0);
}

int	main(void)
{
	t_cli		cli;
	t_parser	parser;
	t_exec		ex;

	minishell_init(&ex);
	cli_init(&cli);
	ignore_parent_sig();
	while (cli_readline(&cli))
	{
		if (cli.line)
		{
			parser_init(&parser, cli.line->str, ex.status, ex.env);
			while (parser_next(&parser))
			{
				exec_init(&parser, &ex);
				exec_run(&ex);
				parser_refresh(&parser, ex.status, ex.env);
			}
		}
	}
	cli_del(&cli);
	return (0);
}
