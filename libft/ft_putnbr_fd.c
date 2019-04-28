/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:23:36 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 16:52:43 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char c;
	long nl;

	nl = n;
	if (nl < 0)
	{
		nl = -nl;
		write(fd, "-", 1);
	}
	if (nl >= 10)
		ft_putnbr_fd(nl / 10, fd);
	c = nl % 10 + '0';
	write(fd, &c, 1);
}
/*
**int main()
**{
**	ft_putnbr(-1000);
**	return(0);
**}
*/
