/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 09:43:38 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:04:49 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t i;
	size_t i2;

	i2 = 0;
	i = -1;
	if (*str2 == '\0')
		return ((char*)str1);
	while (str1[++i] && i < len)
	{
		while (str2[i2] == str1[i + i2] && str2[i2] && (i + i2) < len)
			i2++;
		if (!str2[i2])
			return ((char*)(str1 + i));
	}
	return (NULL);
}
/*
**#include <stdio.h>
**#include <stdlib.h>
**
**int  main(int argc,char **argv)
**{
**	if (argc == 4)
**		printf("ret = %s\n", ft_strnstr(argv[1], argv[2], atoi(argv[3])));
**	return (0);
**}
*/
