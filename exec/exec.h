/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:20:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/20 17:02:52 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include "main.h"
//# include "parse.h"

# define FAIL	0
# define OK		1

int		exec_run(t_parser *e);
char	**env_add(char **env, char *s);
char	**env_remove(char **env, char *s);

int		eq(char *s1, char *s2);
void	print_arr(char **arr, char *name);
void	free_split(char **s);

void	exec_builtin_export(char **argv);
void	exec_builtin_unset(char *key);

#endif
