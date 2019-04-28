/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:21:07 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 16:44:10 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned long i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)(dest + i) = *(unsigned char*)(src + i);
		if (*(unsigned char*)(src + i) == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
/*
**#include <stdio.h>
**
**int main()
**{
**	char str1[50] = "test1";
**	char str2[50] = "TEST2";
**	char str3[50] = "test1";
**	char str4[50] = "TEST2";
**	ft_memccpy(str1, str2,'S', 2);
**	printf("test1 (n == 10 && char == 'S')\n\
**ret = %s\n", ft_memccpy(str1, str2,'S', 10));
**	printf("str1 = %s\n", str1);
**	printf("test1 (n == 2 && char == 'S')\n\
**ret = %s\n", ft_memccpy(str3, str4,'S', 2));
**	printf("str1 = %s\n", str3);
**	return (0);
**}
*/
