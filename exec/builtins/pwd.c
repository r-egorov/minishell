/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:08:26 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 16:09:28 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_pwd(t_exec *e)
{
	(void)e;
	if (!e->pwd)
		return (0);
	//printf("[exec builtin pwd]\n");
	printf("%s\n", e->pwd);
	//write(1, e->pwd, ft_strlen(e->pwd));
	//write(e->fd, "\n", 1);
	return (0);
}