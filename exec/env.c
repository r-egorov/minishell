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

char	*find(char **env, char *key)
{
	int		i;
	char	*match;

	// no '=' in s
	if (ft_strchr(key, '='))
		return (0);
	i = 0;
	while (env[i])
	{
		match = ft_strnstr(env[i], key, ft_strlen(key));
		if (match == env[i] && env[i][ft_strlen(key)] == '=')
			return (match);
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

char	**env_add(char **arr, char *key)
{
	int		count;
	char	**result;
	char	**parts;
	char	*ptr;

	parts = ft_split(key, '=');
	if (parts && parts[0] && parts[1] && !parts[2])
	{
		// key is OK
		if ((ptr = find(arr, parts[0])))
		{
			// already here - update
			//
		}
		else
		{
			// add
		}
	}
	else
	{
		// error
	}

	count = get_count(arr);
	result = malloc(sizeof(*result) * (count + 1 + 1));
	if (!result)
	{
		//error
		return (0);
	}
	copy_arr(result, arr); // replace with memcpy?
	result[count - 1] = ft_strdup(key);
	if (!result[count - 1])
		return (0);//error
	result[count] = 0;
	return (result);
}

char	**env_remove(char **arr, char *key)
{
	int		count;
	char	**result;
	char	*elem;

	elem = find(arr, key);
	printf("found: %p : %s\n", elem, elem);
	if (!elem)
		return (0);
	count = get_count(arr);
	result = malloc(sizeof(*result) * (count));
	if (!result)
	{
		// error
		return (0);
	}
	copy_arr_ex(result, arr, elem);
	result[count] = 0;
	free(elem);
	printf("removed\n");
	return (result);
}


