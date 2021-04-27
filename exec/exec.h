/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:20:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/22 16:15:58 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include "main.h"
//# include "parse.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"

typedef struct	s_exec {
	char	*exec;
	char	**argv;
	char	**envp;
	char	**environ_orig;
	int		fd;
	char	*pwd;

}				t_exec;

# define FAIL	0
# define OK		1

void    exec_init(t_parser *p, t_exec *e);
int		exec_run(t_exec *e);
char	*env_get(char **arr, char *key);
char	**env_add(char **arr, char *key);
char	**env_remove(char **arr, char *key);

int		get_count(char **arr);
void	print_arr(char **arr);
int		eq(char *s1, char *s2);
void	free_split(char **s);

int		exec_builtin_export(t_exec *e, char *param);
int		exec_builtin_unset(t_exec *e, char *key);
int		exec_builtin_pwd(t_exec *e);
int		exec_builtin_env(t_exec *e);

#endif
