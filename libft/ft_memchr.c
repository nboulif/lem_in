/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:21:07 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 16:43:54 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned long i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char*)(s + i) == (unsigned char)c)
			return (s + i);
		i++;
	}
	return (NULL);
}
/*
**#include <stdio.h>
**
**int main()
**{
**	char str1[50] = "pas la lettre dans cette phrase donc NULL";
**	char c2 = 'x';
**	char str3[50] = "lettre 'a' a trouver dans cette phrase";
**	char c = 'a';
**
**	printf("test1 (char == 'x' && n == 44)\n\
**ret = %s\n", ft_memchr(str1, c2, 44));
**	printf("str = %s\n", str1);
**	printf("\ntest2 (char == 'a' && n == 35)\n\
**ret = %s\n", ft_memchr(str3, c, 35));
**	printf("str = %s\n", str3);
**	return (0);
**}
*/
