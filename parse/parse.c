/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:17:45 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/18 18:25:09 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parse_next(t_parse *e)
{
	if (e->pos < ft_strlen(e->line))
	{
		printf("[parse next] got line: %s\n", e->line);
		e->exec = ft_strdup(e->line);
		e->pos = ft_strlen(e->exec);
		return (1);
	}
	return (0);
}
