/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:14:42 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:05:15 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	int c_min;

	c_min = c + 32;
	if (c_min <= 'z' && c_min >= 'a')
		return (c_min);
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
**		printf("ret %d\nen asc = %c\n", ft_tolower(c),(char)ft_tolower(c));
**	}
**	return (0);
**}
*/
