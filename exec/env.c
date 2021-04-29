/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:06:56 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 14:06:57 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find(char **arr, char *key)
{
	int		i;
	char	*match;

	// no '=' in s
	if (ft_strchr(key, '='))
		return (0);
	i = 0;
	while (arr[i])
	{
		match = ft_strnstr(arr[i], key, ft_strlen(key));
		if (match == arr[i] && arr[i][ft_strlen(key)] == '=')
		{
			printf("[env find] found key %s : %s\n", key, match);
			return (match);
		}
		i++;
	}
	return (0);
}

char	*env_get(char **arr, char *key)
{
	char	*s;

	s = find(arr, key);
	if (!s)
		return (0);
	return (ft_strchr(s, '=') + 1);
	//return (0);
}

void	copy_arr(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
}

void	copy_arr_ex(char **dst, char **src, char *s)
{
	int	from;
	int	to;

	from = 0;
	to = 0;
	while (src[from])
	{
		//printf("to: %d, from: %d", to, from);
		if (src[from] != s)
		{
			//printf(" +\n");
			dst[to] = src[from];
			to++;
		}
		from++;
	}
}

int	env_update(char **arr, char *key, char *value)
{
	char	*elem;
	int		i;
	char	*str;

	elem = find(arr, key);
	printf("[env update] elem found: %p : %s\n", elem, elem);
	if (!elem)
		return (-1);
	i = 0;
	while (arr[i])
	{
		if (arr[i] == elem)
		{
			free(arr[i]);
			str = ft_strjoin(key, "=");
			// error if null
			if (!str)
			{
				process_error();
			}
			arr[i] = ft_strjoin(str, value);
			free(str);
			// error if null
			if (!arr[i])
			{
				process_error();
			}
			break ;
		}
		i++;
	}
	return (0);
}

char	**env_add(char **arr, char *pair)
{
	int		count;
	char	**result;
	char	**parts;
	//char	*ptr;
	//int		i;

	parts = ft_split(pair, '=');
	if (parts && parts[0] && parts[1] && !parts[2])
	{
		// key is OK
		if (find(arr, parts[0]))
		{
			// already here - update
			env_update(arr, parts[0], parts[1]);
			return (arr);
		}
	}
	else
	{
		// error
		process_error();
		return (0);
	}

	count = get_count(arr);
	result = malloc(sizeof(*result) * (count + 1 + 1));
	if (!result)
	{
		//error
		process_error();
		return (0);
	}
	copy_arr(result, arr); // replace with memcpy?
	result[count] = ft_strdup(pair);
	if (!result[count])
	{
		process_error();
		return (0);//error
	}
	result[count + 1] = 0;
	return (result);
}

char	**env_remove(char **arr, char *key)
{
	int		count;
	char	**result;
	char	*elem;

	elem = find(arr, key);
	printf("[env remove] found elem: %p : %s\n", elem, elem);
	if (!elem)
		return (0);
	count = get_count(arr) - 1;
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
	{
		// error
		process_error();
		return (0);
	}
	copy_arr_ex(result, arr, elem);
	result[count] = 0;
	free(elem);
	printf("[env remove] elem removed\n");
	return (result);
}
