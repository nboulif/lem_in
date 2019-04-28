/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:14:42 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:05:05 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int c_maj;

	c_maj = c - 32;
	if (c_maj <= 'Z' && c_maj >= 'A')
		return (c_maj);
	return (c);
}
/*
**#include <stdio.h>
**
**int main(int argc, char **argv)
**{
**	char c;
**
**	if (argc == 2)
**	{
**		c = *argv[1];
**		printf("av up c = %c\n", c);
**		printf("ret %d\nen asc = %c\n", ft_toupper(c),(char)ft_toupper(c));
**	}
**	return (0);
**}
*/
