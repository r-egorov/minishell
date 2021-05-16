/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_p2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:01:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 18:15:50 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_env	*make_content(char *key, char *value)
{
	t_env	*result;

	result = malloc(sizeof(*result));
	if (!result)
		process_error();
	result->key = ft_strdup(key);
	if (!result->key)
		process_syserror();
	if (!value)
		result->value = 0;
	else
	{
		result->value = ft_strdup(value);
		if (!result->value)
			process_syserror();
	}
	return (result);
}

t_dlist	*find_by_key(t_dlist *lst, char *key)
{
	t_env	*content;

	while (lst)
	{
		content = lst->content;
		if (eq((content->key), key))
			return (lst);
		lst = lst->next;
	}
	return (0);
}

int	update_by_key(t_exec *e, char *key, char *value, t_ex_op op)
{
	t_dlist	*lst;
	t_env	*content;
	char	*tmp;

	if (!key || !value)
		return (0);
	lst = find_by_key(e->env, key);
	if (lst)
	{
		content = lst->content;
		if (op == EXPORT_APPEND)
		{
			tmp = ft_strjoin(content->value, value);
			if (!tmp)
				process_syserror();
			free(content->value);
			content->value = tmp;
			return (0);
		}
		free(content->value);
		content->value = ft_strdup(value);
		if (!content->value)
			process_syserror();
	}
	return (0);
}

int	add_by_key(t_exec *e, char *key, char *value)
{
	t_env	*content;
	t_dlist	*elem;

	content = make_content(key, value);
	if (!content)
		return (1);
	elem = ft_dlstnew(content);
	if (!elem)
		process_syserror();
	ft_dlstadd_back(&e->env, elem);
	return (0);
}

int	put_env(t_exec *e, char *text)
{
	t_dlist	*lst;
	char	*key;
	char	*value;

	key = get_key(text);
	if (!is_valid_key(key))
	{
		free(key);
		return (1);
	}
	value = get_value(text);
	lst = find_by_key(e->env, key);
	if (lst)
		update_by_key(e, key, value, get_operation(text));
	else
		add_by_key(e, key, value);
	free(key);
	free(value);
	return (0);
}
