/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:28:57 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/15 13:49:29 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*elem;

	if (lst)
	{
		while (*lst)
		{
			elem = *lst;
			*lst = (*lst)->next;
			ft_dlstdelone(elem, del);
		}
	}
}
