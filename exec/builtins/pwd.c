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
	// char	*pwd;

	//printf("[exec builtin pwd]\n");
	printf("%s\n", e->pwd);
	return (0);
	// pwd = getcwd(0, 0);
	// if (pwd)
	// 	printf("%s\n", pwd);
	// free(pwd);
	// return (0);
}
