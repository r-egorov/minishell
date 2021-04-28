/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_search_item.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:23:35 by cisis             #+#    #+#             */
/*   Updated: 2021/04/28 12:24:04 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_btree_search_item(t_btree *root, void *data_ref,
		int (*cmpf)(void *, void *))
{
	void *res;

	res = 0;
	if (root->left)
		res = ft_btree_search_item(root->left, data_ref, cmpf);
	if ((!(res)) && ((*cmpf)(root->item, data_ref) == 0))
		return (root->item);
	if ((!(res)) && (root->right))
		res = ft_btree_search_item(root->right, data_ref, cmpf);
	return (res);
}
