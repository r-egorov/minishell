/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:19:46 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 17:10:39 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	add_slash(char **result, char *s, int from, int to)
{
	char	c;
	char	*tmp;

	c = s[to];
	s[to] = '\0';
	tmp = ft_strjoin(*result, (s + from));
	if (!tmp)
		process_syserror();
	free(*result);
	*result = ft_strjoin(tmp, "\\");
	if (!*result)
		process_syserror();
	free(tmp);
	s[to] = c;
}

static char	*screen_special_chars(char *s)
{
	int		from;
	int		i;
	char	*result;
	char	*tmp;

	if (!s)
		return (0);
	from = 0;
	i = 0;
	result = 0;
	while (s[i])
	{
		if (ft_strchr(SCREEN_SYMBOLS, s[i]))
		{
			add_slash(&result, s, from, i);
			from = i;
		}
		i++;
	}
	tmp = ft_strjoin(result, (s + from));
	if (!tmp)
		process_syserror();
	free(result);
	return (tmp);
}

static int	print_all(t_exec *e, char **arr)
{
	int		i;
	char	*key;
	char	*value;
	int		code;

	code = 0;
	i = 0;
	while (arr[i])
	{
		key = get_key(arr[i]);
		if (!key)
			process_syserror();
		if (printf("%s%s", EXPORT_PREFIX, key) == -1)
			code = 1;
		value = screen_special_chars(get_env(e->env, key));
		if (value)
		{
			printf("=\"%s\"", value);
			free(value);
		}
		printf("\n");
		free(key);
		i++;
	}
	return (code);
}

int	exec_builtin_export(t_exec *e)
{
	int		i;
	int		code;

	code = 0;
	if (!e->argv[1])
		return (print_all(e, sort_str_array(e->envp)));
	i = 1;
	while (e->argv[i])
	{
		if (put_env(&e->env, e->argv[i]))
			code = perr(BLTN_EXPORT_NAME, e->argv[i], ERR_INVALID_ID, 1);
		i++;
	}
	return (code);
}
