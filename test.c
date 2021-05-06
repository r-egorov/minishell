/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:20:36 by lelderbe          #+#    #+#             */
/*   Updated: 2021/05/06 11:35:33 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void	print_arr(char **arr, char *name)
{
	int	i;

	printf("%s\n", name);
	i = 0;
	while (arr[i])
	{
		printf("[%d]: %s\n", i, arr[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	char buf[10];
	char *envp2[] = {"A1=a1", "A2=a2", 0};
	extern char **environ;
	char **old_environ;
	int	fd[2];
	int id;
	int a;
	int y;
	

	pipe(fd);

	a = 42;
	y = 21;
	printf("a: %d, y: %d\n", a, y);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &a, sizeof(int));
		close(fd[1]);
	}
   	else
 	{
		wait(0);
		close(fd[1]);
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("a: %d, y: %d\n", a, y);
	}

	printf("end\n");
	return (0);

	//---------------------
	printf("argc: %d\n", argc);
	printf("   envp pointer : %p\n", envp);
	printf("environ pointer : %p\n", environ);
	print_arr(argv, "argv: ----------");
	envp[29] = "ABC=zzz";
	envp[28] = "";
	print_arr(envp, "envp: ----------");
	print_arr(environ, "environ: ----------");
	read(0, buf, 10);
	printf("getenv('ABC'): %s\n", getenv("ABC"));
	printf("putenv('ABC=aaa')\n");
	putenv("ABC=aaa");
	printf("getenv('ABC'): %s\n", getenv("ABC"));
	printf("environ pointer : %p\n", environ);
	old_environ = environ;
	environ = envp2;
	envp = envp2;
	printf("environ pointer : %p\n", environ);
	print_arr(envp2, "envp2: ----------");
	printf("getenv('ABC'): %s\n", getenv("ABC"));
	printf("putenv('ABC=aaa222')\n");
	putenv("ABC=aaa222");
	printf("getenv('ABC'): %s\n", getenv("ABC"));
	print_arr(envp, "envp: ----------");
	print_arr(environ, "environ: ----------");
	print_arr(old_environ, "old_environ: ----------");
	return (0);
}
