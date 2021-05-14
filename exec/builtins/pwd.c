/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:08:26 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/14 16:08:10 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_pwd(t_exec *e)
{
	int	code;

	code = printf("%s\n", e->pwd);
	if (code == -1)
		return (1);
	return (0);
}
