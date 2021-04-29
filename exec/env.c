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

static char	*find(char **arr, char *key)
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
			//printf("[env find] found key %s : %s\n", key, match);
			return (match);
		}
		i++;
	}
	return (0);
}

/*
char	*env_get(char **arr, char *key)
{
	char	*s;

	s = find(arr, key);
	if (!s)
		return (0);
	return (ft_strchr(s, '=') + 1);
	//return (0);
}
*/

static void	copy_arr(char **dst, char **src)
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

static void	copy_arr_ex(char **dst, char **src, char *s)
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

/*
int	env_update(char **arr, char *key, char *value)
{
	char	*elem;
	int		i;
	char	*str;

	elem = find(arr, key);
	//printf("[env update] elem found: %p : %s\n", elem, elem);
	if (!elem)
		return (-1);
	i = 0;
	while (arr[i])
	{
		if (arr[i] == elem)
		{
			free(arr[i]);
			str = ft_strjoin(key, "=");
			if (!str)
				process_syserror();
			arr[i] = ft_strjoin(str, value);
			free(str);
			if (!arr[i])
				process_syserror();
			break ;
		}
		i++;
	}
	return (0);
}
*/

static int	env_update2(char **arr, char *elem, char *text)
{
	int		i;

	//printf("[env update2] elem : %p : %s\n", elem, elem);
	i = 0;
	while (arr[i])
	{
		if (arr[i] == elem)
		{
			free(arr[i]);
			arr[i] = ft_strdup(text);
			if (!arr[i])
				process_syserror();
			break ;
		}
		i++;
	}
	return (0);
}

char	**env_add(char **arr, char *text)
{
	int		count;
	char	**result;
	char	*ptr;
	char	*elem;

	result = 0;
	ptr = ft_strchr(text, '=');
	if (!ptr)
		return (0);
	*ptr = '\0';
	elem = find(arr, text);
	*ptr = '=';
	if (elem)
	{	// update
		env_update2(arr, elem, text);
	}
	else
	{	// add
		count = get_count(arr) + 1;
		result = malloc(sizeof(*result) * (count + 1));
		if (!result)
			process_syserror();
		copy_arr(result, arr); // replace with memcpy?
		result[count - 1] = ft_strdup(text);
		if (!result[count - 1])
			process_syserror();
		result[count] = 0;
	}
	return (result);
}

char	**env_remove(char **arr, char *key)
{
	int		count;
	char	**result;
	char	*elem;

	elem = find(arr, key);
	//printf("[env remove] found elem: %p : %s\n", elem, elem);
	if (!elem)
		return (0);
	count = get_count(arr) - 1;
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
		process_syserror();
	copy_arr_ex(result, arr, elem);
	result[count] = 0;
	free(elem);
	//printf("[env remove] elem removed\n");
	return (result);
}
