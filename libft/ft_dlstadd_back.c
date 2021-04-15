/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:58:11 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/15 13:46:16 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist		*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = ft_dlstlast(*lst);
			last->next = new;
			new->prev = last;
		
		}
		else
			*lst = new;
	}
}
