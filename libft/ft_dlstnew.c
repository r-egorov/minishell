/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:02:23 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/16 14:37:37 by cisis            ###   ########.fr       */
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
	result->next = NULL;
	result->prev = NULL;
	return (result);
}
