/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:20:42 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/16 15:04:21 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "main.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"
# include <sys/stat.h>
# include <fcntl.h>
# include "env.h"

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
# define ERR_GETCWD_NO_DIR			"cannot access parent directories"

typedef enum e_op {
	READ,
	WRITE,
	APPEND
}			t_op;

// typedef enum e_ex_op {
// 	EXPORT_NOOP,
// 	EXPORT_UPDATE,
// 	EXPORT_APPEND
// }			t_ex_op;

// typedef struct s_env {
// 	char	*key;
// 	char	*value;
// }			t_env;

typedef struct s_exec {
	int		argc;
	char	**argv;
	char	**envp;
	char	*pwd;
	t_dlist	*env;
	t_job	**jobs;
	int		count;
	t_list	*redir_in;
	t_list	*redir_out;
	t_list	*redir_append;
	int		**fd;
	int		status;
}				t_exec;

typedef int (*t_bltn)(t_exec*);

// char	*get_env(t_exec *e, char *key);
// int		put_env(t_exec *e, char *text);
// void	unset_env(t_exec *e, char *key);
// t_dlist	*find_by_key(t_dlist *lst, char *key);
// int		update_by_key(t_exec *e, char *key, char *value, t_ex_op op);

void	exec_init(t_parser *p, t_exec *e);
int		exec_run(t_exec *e);

char	*get_key(char *s);
t_ex_op	get_operation(const char *s);
char	*get_value(const char *s);
char	*get_text(const char *key, const char *value);
int		is_valid_key(const char *key);

int		**create_pipes(int n);
void	pipes_redir(t_exec *e, int job);
void	free_pipes(int **fd);

int		fd_redir(t_exec *e, int job);

int		get_count(char **arr);
int		eq(const char *s1, const char *s2);
void	free_split(char **s);
char	**sort_str_array(char **arr);

int		is_directory(char *path);
int		find_command(t_exec *e, char **s);
int		update_pwd(t_exec *e);

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
