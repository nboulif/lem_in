/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:01:33 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/11 16:55:35 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_lenstr(long n, int acc)
{
	return ((n >= 10) ? ft_lenstr(n / 10, acc + 1) : acc);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	nl;

	nl = n;
	size = ft_lenstr((nl < 0) ? -nl : nl, 1);
	size = (nl < 0) ? size + 1 : size;
	if ((str = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	str[size] = '\0';
	if (nl < 0)
	{
		nl = -nl;
		str[0] = '-';
	}
	if (nl)
		while (nl && size-- && nl)
		{
			str[size] = nl % 10 + '0';
			nl /= 10;
		}
	else
		str[0] = '0';
	return (str);
}
/*
**#include <stdio.h>
**#include <string.h>
**int main (int argc, char **argv)
**{
**	char *i1 = ft_itoa(-623);
**	char *i2 = ft_itoa(156);
**	char *i3 = ft_itoa(-0);
**	if (argc == 2)
**		printf("%s\n", ft_itoa(atoi(argv[1])));
**	printf ("%d\n",strcmp(i1, "-623"));
**	printf ("%d\n",strcmp(i2, "156"));
**	printf ("%d\n",strcmp("0", i3));
**	return (0);
**}
*/
