/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:38:29 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/12 19:23:38 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	fd_redir_do(t_list *lst, t_op op, int oflag)
{
	int	fd;

	fd = 0;
	while (lst)
	{
		if (fd)
			close(fd);
		fd = open((char *)lst->content, oflag, 0666);
		if (fd == -1)
		{
			printf("%s: %s: %s\n", APP_NAME, lst->content, strerror(errno));
			return (-1);
		}
		lst = lst->next;
	}
	if (op == READ)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	fd_redir(t_exec *e, int job)
{
	int	result;

	result = 0;
	if (e->jobs[job]->redir_in)
		result = fd_redir_do(e->jobs[job]->redir_in, READ, O_RDONLY);
	if (e->jobs[job]->redir_append)
		result = fd_redir_do(e->jobs[job]->redir_append, \
								APPEND, O_WRONLY | O_APPEND | O_CREAT);
	if (e->jobs[job]->redir_out)
		result = fd_redir_do(e->jobs[job]->redir_out, \
								WRITE, O_WRONLY | O_CREAT | O_TRUNC);
	return (result);
}
