/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:06:56 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/20 16:56:54 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i + 1);
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
}

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
}

char	**env_add(char **env, char *s)
{
	int		count;
	char	**result;
	char	**parts;
	char	*ptr;

	parts = ft_split(s, '=');
	if (parts && parts[0] && parts[1] && !parts[2])
	{
		// s is OK
		if ((ptr = find(env, parts[0])))
		{
			// already here - update
			//f
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


	count = get_count(env);
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
	{
		//error
		return (0);
	}
	copy_arr(result, env); // replace with memcpy?
	result[count - 1] = s;
	result[count] = 0;
	return (result);
}

char	**env_remove(char **env, char *s)
{
	int		count;
	char	**result;
	char	*elem;

	elem = find(env, s);
	if (!elem)
		return (0);
	count = get_count(env);
	result = malloc(sizeof(*result) * (count - 1));
	if (!result)
	{
		//error
		return (0);
	}
	copy_arr_ex(result, env, elem);
	result[count - 1] = 0;
	printf("removed\n");
	return (result);
}


