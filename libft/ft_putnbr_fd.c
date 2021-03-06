/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:38:08 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/04 14:39:47 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n / 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
	}
	if (n < 0)
	{
		c = '0' + (-1) * (n % 10);
	}
	else
	{
		c = '0' + (n % 10);
	}
	write(fd, &c, 1);
}
