/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:20:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/28 12:52:27 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include "main.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"
# include <sys/stat.h>

# define FAIL	0
# define OK		1

# define BUILTIN_CD_NAME			"cd"
# define BUILTIN_UNSET_NAME			"unset"
# define ERR_EXEC_CD_TOO_MANY_ARGS	"too many arguments"
# define ERR_EXEC_UNSET_INVALID_ID	"not a valid identifier"
# define ERR_COMMAND_NOT_FOUND		"command not found"

typedef struct	s_exec {
	char	*exec;
	char	**argv;
	char	**envp;
	char	**environ_orig;
	int		fd;
	char	*pwd;

}				t_exec;

void    exec_init(t_parser *p, t_exec *e);
int		exec_run(t_exec *e);
//char	*env_get(char **arr, char *key);
char	**env_add(char **arr, char *key);
char	**env_remove(char **arr, char *key);
int		env_update(char **arr, char *key, char *value);

int		get_count(char **arr);
void	print_arr(char **arr);
int		eq(char *s1, char *s2);
void	free_split(char **s);

char	*get_path(const char *s);

int		exec_builtin_export(t_exec *e);
int		exec_builtin_unset(t_exec *e);
int		exec_builtin_pwd(t_exec *e);
int		exec_builtin_env(t_exec *e);
int		exec_builtin_cd(t_exec *e);

#endif
