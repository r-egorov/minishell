/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:53:40 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/15 13:54:05 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*result;

	result = 0;
	while (lst)
	{
		result = lst;
		lst = lst->next;
	}
	return (result);
}
