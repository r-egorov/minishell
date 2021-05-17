/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 18:36:17 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	minishell_init(t_exec *e)
{
	extern char	**environ;
	int			i;

	ft_bzero(e, sizeof(e));
	i = 0;
	while (environ[i])
	{
		put_env(&e->env, environ[i]);
		i++;
	}
	update_pwd(e);
	return (0);
}

void	print_job(t_job *job)
{
	char	**argv;
	t_list	*list;

	argv = job->argv;
	printf("=====\nCMD |%s|\nARGV\n", job->cmd);
	while (*argv)
		printf("|%s|\n", *argv++);
	list = job->redir_in;
	printf("======\nREDIR_IN\n");
	while (list)
	{
		printf("|%s|\n", (char *)list->content);
		list = list->next;
	}
	list = job->redir_out;
	printf("======\nREDIR_OUT\n");
	while (list)
	{
		printf("|%s|\n", (char *)list->content);
		list = list->next;
	}
	list = job->redir_append;
	printf("======\nREDIR_APPEND\n");
	while (list)
	{
		printf("|%s|\n", (char *)list->content);
		list = list->next;
	}
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
		//printf("input = |%s|\nlen = %d\n", cli.line->str, cli.line->len);
		if (cli.line)
		{
			parser_init(&parser, cli.line->str, ex.status);
			while (parser_next(&parser))
			{
				/*
				size_t j = 0;
				while (j < parser.jobs_len)
				{
					printf("---\nJOB N%zu\n---\n", j);
					print_job(parser.jobs[j]);
					j++;
				}
				*/
				exec_init(&parser, &ex);
				exec_run(&ex);
				parser_refresh(&parser, ex.status);
			}
		}
	}
	cli_del(&cli);
	return (0);
}
