/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/05 16:05:49 by cisis            ###   ########.fr       */
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
	//e->fd = 1;
	return (1);
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
		printf("|%s|\n", (char*)list->content);
		list = list->next;
	}
	list = job->redir_out;
	printf("======\nREDIR_OUT\n");
	while (list)
	{
		printf("|%s|\n", (char*)list->content);
		list = list->next;
	}
	list = job->redir_append;
	printf("======\nREDIR_APPEND\n");
	while (list)
	{
		printf("|%s|\n", (char*)list->content);
		list = list->next;
	}
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

	//signal(SIGINT, sigint_handler);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	while (cli_readline(&cli))
	{
		//printf("input = |%s|\nlen = %d\n", cli.line->str, cli.line->len);
		if (cli.line->len > 0)
		{
			parser_init(&parser, cli.line->str);
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
				//printf("[main] envp | environ addr : %p | %p\n", ex.envp, environ);
				//printf("[main] PWD: %s\n", getenv("PWD"));
				//printf("[main] AA: %s\n", getenv("AA"));
				environ = ex.envp;
				//printf("[main] envp | environ addr : %p | %p\n", ex.envp, environ);
				//printf("[main] PWD: %s\n", getenv("PWD"));
				//printf("[main] AA: %s\n", getenv("AA"));
				parser_clean(&parser);
			}
		}
		//printf("[main] end parser loop - next cli loop\n");
	}
	//printf("[main] end cli loop\n");
	cli_del(&cli);

	return (0);
}
