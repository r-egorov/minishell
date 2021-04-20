/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:40:06 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/20 16:43:08 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_arr(char **arr, char *name)
{
	int	i;

	printf("%s\n", name);
	i = 0;
	while (arr[i])
	{
		printf("[%d]: %s\n", i, arr[i]);
		i++;
	}
}

int	eq(char *s1, char *s2)
{
	int	len;

	if (!s1 || !s2)
		return (FAIL);
	len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
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
