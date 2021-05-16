/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 20:05:53 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 18:16:29 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	copy_arr_ex(char **dst, char **src, char *s)
{
	int	from;
	int	to;

	from = 0;
	to = 0;
	while (src[from])
	{
		if (src[from] != s)
		{
			dst[to] = src[from];
			to++;
		}
		from++;
	}
	dst[to] = src[from];
}

char	**get_copy_arr(char **arr)
{
	char	**result;
	int		count;
	int		i;

	count = get_count(arr);
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
		process_syserror();
	i = 0;
	while (arr[i])
	{
		result[i] = arr[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

char	**sort_str_array(char **arr)
{
	int		i;
	int		j;
	int		count;
	char	*ptr;

	count = get_count(arr);
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j] + 1)) > 0)
			{
				ptr = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = ptr;
			}
			j++;
		}
		i++;
	}
	return (arr);
}
