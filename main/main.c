/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:49:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/13 11:25:31 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	minishell_init(t_exec *e)
{
	extern char	**environ;
	int			i;
	t_dlist		*lst;
	t_env		*elem;

	ft_bzero(e, sizeof(e));
	i = 0;
	while (environ[i])
	{
		put_env(e, environ[i]);
		i++;
	}
	update_pwd(e);
	//e->pwd = get_pwd(e);
	/*
	lst = e->env;
	while (lst)
	{
		elem = lst->content;
		printf("%s%s=%s%s\n", ORANGE, elem->key, elem->value, DEFAULT);
		lst = lst->next;
	}
	printf("key: PWD, value: %s\n", get_env(e, "PWD"));
	printf("key: HOME, value: %s\n", get_env(e, "HOME"));
	*/
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

	minishell_init(&ex);
	cli_init(&cli);
	

	(void)argc;
	(void)argv;
	(void)envp;

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

				//printf("[main] envp | environ addr : %p | %p\n", ex.envp, environ);
				//printf("[main] PWD: %s\n", getenv("PWD"));
				//printf("[main] AA: %s\n", getenv("AA"));
				
				//environ = ex.envp;
				
				//printf("[main] envp | environ addr : %p | %p\n", ex.envp, environ);
				//printf("[main] PWD: %s\n", getenv("PWD"));
				//printf("[main] AA: %s\n", getenv("AA"));
				parser_refresh(&parser, ex.status);
			}
		}
		//printf("[main] end parser loop - next cli loop\n");
	}
	//printf("[main] end cli loop\n");
	cli_del(&cli);
	//environ = ex.environ_orig;
	return (0);
}
