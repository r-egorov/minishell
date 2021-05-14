/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:06:56 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/14 18:13:43 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find(char **arr, char *key)
{
	int		i;
	char	*match;

	if (ft_strchr(key, '='))
		return (0);
	i = 0;
	while (arr[i])
	{
		match = ft_strnstr(arr[i], key, ft_strlen(key));
		if (match == arr[i] && (arr[i][ft_strlen(key)] == '=' \
									|| arr[i][ft_strlen(key)] == '\0'))
			return (match);
		i++;
	}
	return (0);
}

static int	env_update(char **arr, char *elem, char *text)
{
	int		i;
	char	*value;

	value = get_value(text);
	if (!value)
		return (0);
	free(value);
	i = 0;
	while (arr[i])
	{
		if (arr[i] == elem)
		{
			free(arr[i]);
			arr[i] = ft_strdup(text);
			// arr[i] = ft_strjoin(get(keytext);
			if (!arr[i])
				process_syserror();
			break ;
		}
		i++;
	}
	return (0);
}
/*
char	*get_new_text(char *text)
{
	char		*key;
	char		*value;
	t_exp_op	op;
	char		*result;

	key = get_key(text);
	value = get_value(text);
	op = get_operation(text);
	if (!value)
		return (key);
	result = ft_strjoin(key, "=");
	if (!result)
		process_syserror();
	free(key);
	key = ft_strjoin(result, value);
	if (!key)
		process_syserror();
	free(value);
	return (key);
}
*/
char	**env_add(char **arr, char *text)
{
	int			count;
	char		**result;
	char		*elem;
	char		*key;
	// t_exp_op	op;

	result = arr;
	key = get_key(text);
	if (!key || !is_valid_key(key))
	{
		free(key);
		perr(BLTN_EXPORT_NAME, text, ERR_INVALID_ID, 0);
		return (0);
	}
	// op = get_operation(text);
	elem = find(arr, key);
	free(key);
	if (elem)
		env_update(arr, elem, text);
	else
	{
		count = get_count(arr) + 1;
		result = malloc(sizeof(*result) * (count + 1));
		if (!result)
			process_syserror();
		copy_arr_ex(result, arr, NULL);
		result[count - 1] = ft_strdup(text);
		// result[count - 1] = ft_strjoin(get_key(text), get_value(text));
		if (!result[count - 1])
			process_syserror();
		result[count] = 0;
	}
	// free(key);
	return (result);
}

char	**env_remove(char **arr, char *key)
{
	int		count;
	char	**result;
	char	*elem;

	elem = find(arr, key);
	if (!elem)
		return (0);
	count = get_count(arr) - 1;
	result = malloc(sizeof(*result) * (count + 1));
	if (!result)
		process_syserror();
	copy_arr_ex(result, arr, elem);
	result[count] = 0;
	free(elem);
	return (result);
}
