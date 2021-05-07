/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:17:52 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/07 11:58:40 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_dlist *lst, void (*del)(void*))
{
	if (lst)
	{
		if (lst->content)
		{
			del(lst->content);
			lst->content = NULL;
		}
		free(lst);
		lst = NULL;
	}
}
