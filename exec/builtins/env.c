/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:11:36 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/14 18:14:55 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_env(t_exec *e)
{
	char	*value;
	t_dlist	*lst;
	t_env	*content;

	lst = e->env;
	while (lst)
	{
		content = lst->content;
		if (content->value)
			printf("%s=%s\n", content->key, content->value);
		lst = lst->next;
	}
	return (0);
}
