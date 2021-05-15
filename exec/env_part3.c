/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_part3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:01:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/13 13:02:52 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_text(const char *key, const char *value)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		process_syserror();
	result = ft_strjoin(tmp, value);
	if (!result)
		process_syserror();
	free(tmp);
	return (result);
}

char	*get_key(char *s)
{
	char	*ptr;
	char	*key;
	char	c;

	if (!s || ft_strlen(s) == 0)
		return (0);
	ptr = ft_strchr(s, '=');
	if (ptr)
	{
		if (ptr != s && *(ptr - 1) == '+')
			ptr = ptr - 1;
		c = *ptr;
		*ptr = '\0';
	}
	key = ft_strdup(s);
	if (!key)
		process_syserror();
	if (ptr)
		*ptr = c;
	return (key);
}

t_ex_op	get_operation(const char *s)
{
	char	*ptr;

	if (!s || ft_strlen(s) == 0)
		return (EXPORT_NOOP);
	ptr = ft_strchr(s, '=');
	if (!ptr)
		return (EXPORT_NOOP);
	if (ptr != s && *(ptr - 1) == '+')
		return (EXPORT_APPEND);
	return (EXPORT_UPDATE);
}

char	*get_value(const char *s)
{
	char	*ptr;
	char	*value;

	if (!s || ft_strlen(s) == 0)
		return (0);
	ptr = ft_strchr(s, '=');
	if (!ptr)
		return (0);
	value = ft_strdup(ptr + 1);
	if (!value)
		process_syserror();
	return (value);
}

int	is_valid_key(const char *key)
{
	int		i;

	if (!key)
		return (FAIL);
	i = 0;
	while (key[i])
	{
		if (i == 0 && ft_isdigit(key[i]))
			return (FAIL);
		if (!(ft_strchr("_", key[i]) || ft_isalnum(key[i])))
			return (FAIL);
		i++;
	}
	return (OK);
}
