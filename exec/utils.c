/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:40:06 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 16:13:39 by lelderbe         ###   ########.fr       */
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

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		//printf("[%d]: %s\n", i, arr[i]);
		printf("%s\n", arr[i]);
		i++;
	}
}

int	eq(const char *s1, const char *s2)
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

void	sort_str_array(char **arr)
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
}

