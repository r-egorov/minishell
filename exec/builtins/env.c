/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:11:36 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 14:51:11 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_env(t_exec *e)
{
	t_dlist	*lst;
	t_env	*content;
	int		code;

	code = 0;
	lst = e->env;
	while (lst)
	{
		content = lst->content;
		if (content->value)
			if (printf("%s=%s\n", content->key, content->value) == -1)
				code = 1;
		lst = lst->next;
	}
	return (code);
}
