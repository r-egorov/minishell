/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_p1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:06:56 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 18:16:00 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_env(t_exec *e, char *key)
{
	t_dlist	*lst;
	t_env	*content;

	lst = e->env;
	while (lst)
	{
		content = lst->content;
		if (eq((content->key), key))
			return (content->value);
		lst = lst->next;
	}
	return (0);
}

void	unset_env(t_exec *e, char *key)
{
	t_dlist	*lst;
	t_dlist	*head;

	lst = find_by_key(e->env, key);
	if (lst)
	{
		if (!lst->prev)
			head = lst->next;
		else
			head = e->env;
		free(((t_env *)lst->content)->key);
		free(((t_env *)lst->content)->value);
		ft_dlstdelone(lst, free);
		e->env = head;
	}
}
