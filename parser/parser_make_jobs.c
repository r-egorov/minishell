/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_jobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:35:33 by cisis             #+#    #+#             */
/*   Updated: 2021/05/04 18:34:53 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	job_del(t_job *self)
{
	if (self)
	{
		if (self->argv)
		{
			ft_free_strs(self->argv);
			self->argv = NULL;
		}
		free_str(self->redir_in);
		free_str(self->redir_out);
		free_str(self->redir_append);
		free(self);
	}
}

t_job	*job_new(void)
{
	t_job	*job;

	job = (t_job *)malloc(sizeof(t_job));
	if (!job)
		return (NULL);
	job->cmd = NULL;
	job->argv = NULL;
	job->argc = 0;
	job->redir_in = NULL;
	job->redir_out = NULL;
	job->redir_append = NULL;
	job->del = job_del;
	return (job);
}

void	print_job(t_job *job)
{
	char	**argv;

	argv = job->argv;
	printf("=====\nCMD |%s|\nARGV\n", job->cmd);
	while (*argv)
		printf("|%s|\n", *argv++);
	printf("REDIN |%s|\nREDOUT |%s|\nREDAPP |%s|\n", job->redir_in, job->redir_out, job->redir_append);
}

void	job_append_arg(t_job *self, char *arg)
{
	char	**tmp;
	size_t	i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (self->argc + 2));
	if (!tmp || !arg)
		process_syserror();
	if (self->argc == 0)
	{
		tmp[0] = arg;
		tmp[1] = NULL;
	}
	else
	{
		while (self->argv[i])
		{
			tmp[i] = self->argv[i];
			i++;
		}
		tmp[i] = arg;
		tmp[++i] = NULL;
		free(self->argv);
	}
	self->argv = tmp;
	self->argc += 1;
}

void	parser_append_job(t_parser *self, t_job *job)
{
	t_job	**tmp;
	size_t	i;

	i = 0;
	tmp = (t_job **)malloc(sizeof(t_job) * (self->jobs_len + 2));
	if (!tmp)
		process_syserror();
	if (self->jobs_len == 0)
	{
		tmp[0] = job;
		tmp[1] = NULL;
	}
	else
	{
		while (self->jobs[i])
		{
			tmp[i] = self->jobs[i];
			i++;
		}
		tmp[i] = job;
		tmp[++i] = NULL;
		free(self->jobs);
	}
	self->jobs = tmp;
	self->jobs_len += 1;
}

int		parser_make_jobs(t_parser *self)
{
	size_t	i;
	size_t	tokens_len;
	t_token	**tokens;
	t_job	*job;

	i = self->pos;
	tokens_len = self->lexer->tokens_len;
	tokens = self->lexer->tokens;
	while (i < tokens_len && tokens[i]->type != SEP)
	{
		job = job_new();
		if (tokens[i]->type == PIPE)
			i++;
		while (i < tokens_len && (tokens[i]->type != PIPE
					&& tokens[i]->type != SEP))
		{
			if ((tokens[i]->type == CMD) || (tokens[i]->type == ARG))
				job_append_arg(job, ft_strdup(tokens[i]->str));
			else if (tokens[i]->type == REDIR_IN)
			{
				i++;
				job->redir_in = ft_strdup(tokens[i]->str);
				if (!job->redir_in)
					process_syserror();
			}
			else if (tokens[i]->type == REDIR_OUT)
			{
				i++;
				job->redir_out = ft_strdup(tokens[i]->str);
				if (!job->redir_out)
					process_syserror();
			}
			else if (tokens[i]->type == REDIR_APPEND)
			{
				i++;
				job->redir_append = ft_strdup(tokens[i]->str);
				if (!job->redir_append)
					process_syserror();
			}
			i++;
		}
		job->cmd = job->argv[0];
		print_job(job);
		parser_append_job(self, job);
	}
	return (0);
}
