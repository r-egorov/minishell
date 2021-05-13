/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_part2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:01:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/13 13:02:52 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_key(char *s)
{
	char	*ptr;
	char	*key;

	if (ft_strlen(s) == 0)
		return (0);
	ptr = ft_strchr(s, '=');
	if (ptr)
		*ptr = '\0';
	key = ft_strdup(s);
	if (!key)
		process_syserror();
	if (ptr)
		*ptr = '=';
	return (key);
}

char	*get_value(char *s)
{
	char	*ptr;
	char	*value;

	if (ft_strlen(s) == 0)
		return (0);
	ptr = ft_strchr(s, '=');
	if (!ptr)
		return (0);
	*ptr = '\0';
	value = ft_strdup(ptr + 1);
	if (!value)
		process_syserror();
	*ptr = '=';
	return (value);
}

int	is_valid_key(char *key)
{
	int		i;

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
