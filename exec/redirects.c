/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:38:29 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/12 14:39:40 by lelderbe         ###   ########.fr       */
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
		// if (op == READ)
		fd = open((char *)lst->content, oflag, 0666);
		// else if (op == WRITE)
			// fd = open((char *)lst->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		// else
			// fd = open((char *)lst->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		// fprintf(stderr, "fd open : %d for file: %s\n", fd, lst->content);
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

	(void)job;
	if (e->redir_in)
	// {
		result = fd_redir_do(e->redir_in, READ, O_RDONLY);
	// 	if (result == -1)
	// 	{
	// 		// printf("%s: %s: %s\n", APP_NAME, e->argv[0], strerror(errno));
	// 		return (-1);
	// 	}
	// }
	if (e->redir_append)
	// {
		result = fd_redir_do(e->redir_append, APPEND, O_WRONLY | O_APPEND | O_CREAT);
	// 	if (result == -1)
	// 	{
	// 		// printf("%s: %s: %s\n", APP_NAME, e->argv[0], strerror(errno));
	// 		return (-1);
	// 	}
	// }
	if (e->redir_out)
	// {
		result = fd_redir_do(e->redir_out, WRITE, O_WRONLY | O_CREAT | O_TRUNC);
	// 	if (result == -1)
	// 	{
	// 		// printf("%s: %s: %s\n", APP_NAME, e->argv[0], strerror(errno));
	// 		return (-1);
	// 	}
	// }
	return (0);
}
