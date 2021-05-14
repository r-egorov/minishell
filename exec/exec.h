/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:20:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/14 18:07:51 by lelderbe         ###   ########.fr       */
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
# include <fcntl.h>

# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define ORANGE		"\033[0;33m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define DEFAULT	"\033[0m"
# define DCOLOR		GREEN
# define BLT_COLOR	GREEN
# define PCOLOR		GREEN

# define EXPORT_PREFIX				"declare -x "
# define SCREEN_SYMBOLS				"$\\\'\""

# define BLTN_CD_NAME				"cd"
# define BLTN_EXPORT_NAME			"export"
# define BLTN_UNSET_NAME			"unset"
# define BLTN_EXIT_NAME				"exit"
# define BLTN_ECHO_NAME				"echo"
# define BLTN_ENV_NAME				"env"
# define BLTN_PWD_NAME				"pwd"

# define ERR_TOO_MANY_ARGS			"too many arguments"
# define ERR_INVALID_ID				"not a valid identifier"
# define ERR_COMMAND_NOT_FOUND		"command not found"
# define ERR_IS_A_DIRECTORY			"is a directory"
# define ERR_CD_HOME_NOT_SET		"HOME not set"
# define ERR_NUMERIC_REQ			"numeric argument required"


typedef enum e_op {
	READ,
	WRITE,
	APPEND
}			t_op;

typedef enum e_exp_op {
	EXPORT_NOOP,
	EXPORT_UPDATE,
	EXPORT_JOIN
}			t_exp_op;

typedef struct s_exec {
	int		argc;
	char	**argv;
	char	**envp;
	char	**environ_orig;
	int		fd0;
	int		fd1;
	t_job	**jobs;
	int		count;
	t_list	*redir_in;
	t_list	*redir_out;
	t_list	*redir_append;
	int		**fd;
	int		status;
	char	*pwd;
}				t_exec;

typedef int (*t_bltn)(t_exec*);

void	exec_init(t_parser *p, t_exec *e);
int		exec_run(t_exec *e);

char	**env_add(char **arr, char *key);
char	**env_remove(char **arr, char *key);
//int		env_update(char **arr, char *key, char *value);
char	*find(char **arr, char *key);

char	*get_key(char *s);
char	*get_value(char *s);
int		is_valid_key(char *key);

int		**create_pipes(int n);
void	pipes_redir(t_exec *e, int job);
void	free_pipes(int **fd);

int		fd_redir(t_exec *e, int job);

int		get_count(char **arr);
int		eq(const char *s1, const char *s2);
void	free_split(char **s);
char	**get_copy_arr(char **arr);
char	**sort_str_array(char **arr);
void	copy_arr_ex(char **dst, char **src, char *s);

int		find_command(char **s);
int		is_directory(char *path);
char	*get_pwd(t_exec *e);

int		match_builtin(const char *s);
int		exec_builtins(t_exec *e, int idx, int job);
int		exec_builtin_export(t_exec *e);
int		exec_builtin_unset(t_exec *e);
int		exec_builtin_pwd(t_exec *e);
int		exec_builtin_env(t_exec *e);
int		exec_builtin_cd(t_exec *e);
int		exec_builtin_echo(t_exec *e);
int		exec_builtin_exit(t_exec *e);

#endif
