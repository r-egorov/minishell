/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:06:56 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/19 18:09:45 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#define	FAIL	1
#define	OK		0

void	free_split(char **s)
{
	long	i;

	i = 0;
	while (s && s[i])
		free(s[i++]);
	free(s);
}

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

int		eq(char *s1, char *s2)
{
	int	len;

	if (!s1 || !s2)
		return (FAIL);
	len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
	if (ft_strncmp(s1, s2, len) == 0)
		return (OK);
	return (FAIL);
}

char	*find(char **env, char *s)
{
	int		i;
	char	*match;

	// no '=' in s
	if (ft_strchr(s, '='))
		return (0);
	i = 0;
	while (env[i])
	{
		match = ft_strnstr(env[i], s, ft_strlen(s));
		if (match == env[i])
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

	count = get_count(env);
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
	{
		//error
		return (0);
	}
	copy_arr(result, env);
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
	return (result);
}


