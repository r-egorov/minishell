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
//# include <stdarg.h>
# include <fcntl.h>

# define FAIL		0
# define OK			1

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

# define BUILTIN_CD_NAME			"cd"
# define BUILTIN_UNSET_NAME			"unset"
# define ERR_EXEC_CD_TOO_MANY_ARGS	"too many arguments"
# define ERR_EXEC_UNSET_INVALID_ID	"not a valid identifier"
# define ERR_COMMAND_NOT_FOUND		"command not found"
# define ERR_IS_A_DIRECTORY			"is a directory"
# define ERR_EXEC_CD_HOME_NOT_SET	"HOME not set"

typedef enum	e_op {
	READ,
	WRITE,
	APPEND
}				t_op;

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
}				t_exec;

void	exec_init(t_parser *p, t_exec *e);
int		exec_run(t_exec *e);
char	**env_add(char **arr, char *key);
char	**env_remove(char **arr, char *key);
int		env_update(char **arr, char *key, char *value);

char	*get_key(char *s);
char	*get_value(char *s);

int		**prepare_pipes(int n);
void	pipes_redir(t_exec *e, int job);
void	free_pipes(int **fd);

int		fd_redir(t_exec *e, int job);

int		get_count(char **arr);
void	print_arr(char **arr);
int		eq(const char *s1, const char *s2);
void	free_split(char **s);
char	**get_copy_arr(char **arr);
void	sort_array(char **arr);

int		find_command(char **s);
int		is_directory(char *path);

int		match_builtin(const char *s);
int		exec_builtins(t_exec *e, int idx, int job);
int		exec_builtin_export(t_exec *e);
int		exec_builtin_unset(t_exec *e);
int		exec_builtin_pwd(t_exec *e);
int		exec_builtin_env(t_exec *e);
int		exec_builtin_cd(t_exec *e);
int		exec_builtin_echo(t_exec *e);

#endif
