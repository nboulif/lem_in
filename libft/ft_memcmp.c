/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:21:07 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 16:44:21 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char*)(s1 + i) != *(unsigned char*)(s2 + i))
			return (*(unsigned char*)(s1 + i) - *(unsigned char*)(s2 + i));
		i++;
	}
	return (0);
}
/*
**#include <stdio.h>
**
**int main()
**{
**	char str1[50] = "une phrase";
**	char str3[50] = "un autre phrase";
**
**	printf("test1 (n == 9)\n\
**ret = %s\n", ft_memchr(str1, str3, 9));
**	printf("str = %s\n", str1);
**	return (0);
**}
*/
