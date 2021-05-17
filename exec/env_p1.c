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

char	*get_env(t_dlist *lst, char *key)
{
	//t_dlist	*lst;
	t_env	*content;

	//lst = e->env;
	while (lst)
	{
		content = lst->content;
		if (eq((content->key), key))
			return (content->value);
		lst = lst->next;
	}
	return (0);
}

void	unset_env(t_dlist **lst, char *key)
{
	t_dlist	*elem;
	t_dlist	*head;

	if (lst && *lst)
	{
		elem = find_by_key(*lst, key);
		if (elem)
		{
			if (!elem->prev)
				head = elem->next;
			else
				head = *lst;
				// head = e->env;
			free(((t_env *)elem->content)->key);
			free(((t_env *)elem->content)->value);
			ft_dlstdelone(elem, free);
			*lst = head;
		}
	}
}
