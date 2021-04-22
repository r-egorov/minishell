/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:08:26 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 14:54:39 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_pwd(t_exec *e)
{
	(void)e;
	if (!e->pwd)
		return (0);
	//printf("[exec builtin pwd]\n");
	write(e->fd, e->pwd, ft_strlen(e->pwd));
	write(e->fd, "\n", 1);
	return (0);
}
