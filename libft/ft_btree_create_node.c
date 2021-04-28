/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:00:18 by cisis             #+#    #+#             */
/*   Updated: 2021/04/28 12:01:03 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*ft_btree_create_node(void *item)
{
	t_btree	*res;

	res = (t_btree*)malloc(sizeof(t_btree));
	if (!res)
		return (NULL);
	res->item = item;
	res->left = NULL;
	res->right = NULL;
	return (res);
}
