/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:20:36 by lelderbe          #+#    #+#             */
/*   Updated: 2021/04/19 16:17:40 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
