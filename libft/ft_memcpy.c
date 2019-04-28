/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:21:07 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 16:45:56 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long i;

	i = -1;
	while (++i < n)
		*(unsigned char*)(dest + i) = *(unsigned char*)(src + i);
	return (dest);
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
**	printf("test1 (n == 5)\n\
**ret = %s\n", ft_memcpy(str1, str2, 5));
**	printf("str1 = %s\n", str1);
**	printf("test1 (n == 3)\n\
**ret = %s\n", ft_memcpy(str3, str4, 3));
**	printf("str1 = %s\n", str3);
**	return (0);
**}
*/
