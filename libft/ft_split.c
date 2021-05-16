/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:48:38 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 16:11:03 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_parts_count(char const *s, char c)
{
	int	count;
	int	out;

	count = 0;
	out = 1;
	while (*s)
	{
		if (*s == c)
			out = 1;
		else if (out)
		{
			count++;
			out = 0;
		}
		s++;
	}
	return (count);
}

static void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static char	*get_next_part(char const *s, char c)
{
	char	*result;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	result = malloc(sizeof(*result) * (i + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, s, i + 1);
	return (result);
}

static int	fill_split(char **arr, char const *s, char c, int parts)
{
	int	part;

	part = 0;
	while (part < parts)
	{
		if (*s == c)
			s++;
		else
		{
			arr[part] = get_next_part(s, c);
			if (!arr[part])
				return (-1);
			s = s + ft_strlen(arr[part]);
			part++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		parts;

	if (!s)
		return (0);
	parts = get_parts_count(s, c);
	result = ft_calloc(parts + 1, sizeof(*result));
	if (!result)
		return (0);
	if (fill_split(result, s, c, parts) == -1)
	{
		free_split(result);
		return (0);
	}
	return (result);
}
