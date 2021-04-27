/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 14:54:07 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	minishell_init(t_exec *e)
{
	extern char **environ;
	int			count;
	int			i;
	char		**result;

	ft_bzero(e, sizeof(e));
	count = get_count(environ);
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
	{
		//error
		return (0);
	}
	i = 0;
	while (environ[i])
	{
		result[i] = ft_strdup(environ[i]);
		if (!result[i])
		{
			// error
			free_split(result);
			return (0);
		}
		i++;
	}
	result[count] = 0;
	e->environ_orig = environ;
	e->envp = result;
	environ = result;
	//e->pwd = ft_strdup(env_get(e->envp, "PWD"));
	//e->fd = 1;
	return (1);
}

int		main(int argc, char** argv, char **envp)
{
	extern char **environ;
	t_cli		cli;
	t_parser	parser;
	t_exec		ex;

	if (!minishell_init(&ex))
	{
		// init error
		exit(1);
	}

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
			printf("PWD: %s\n", getenv("PWD"));
			exec_init(&parser, &ex);
			exec_run(&ex);
			environ = ex.envp;
			free(parser.exec);
			free_split(parser.argv);
		}
	}
	cli_del(&cli);

	free(ex.pwd);
	return (0);
}
