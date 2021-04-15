/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:02:23 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/15 13:31:42 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*result;

	result = malloc(sizeof(t_dlist));
	if (!result)
		return (0);
	result->content = content;
	result->next = 0;
	result->prev = 0;
	return (result);
}
