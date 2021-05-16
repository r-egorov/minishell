/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:40:06 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 18:16:22 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	eq(const char *s1, const char *s2)
{
	int	len;

	if (!s1 && !s2)
		return (OK);
	if (!s1 || !s2)
		return (FAIL);
	if (ft_strlen(s1) > ft_strlen(s2))
		len = ft_strlen(s1);
	else
		len = ft_strlen(s2);
	if (ft_strncmp(s1, s2, len) == 0)
		return (OK);
	return (FAIL);
}

void	free_split(char **s)
{
	long	i;

	i = 0;
	while (s && s[i])
		free(s[i++]);
	free(s);
}
