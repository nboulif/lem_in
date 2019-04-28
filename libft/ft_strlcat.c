/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:18:57 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:00:33 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t i2;
	size_t size_dst;

	i2 = 0;
	if ((i = ft_strlen(dst)) + 1 > size)
		return (ft_strlen((char*)src) + size);
	size_dst = i;
	while (i < size - 1 && src[i2])
		dst[i++] = src[i2++];
	dst[i] = '\0';
	return (size_dst + ft_strlen(src));
}
/*
**#include <stdio.h>
**
**int main(int argc, char **argv)
**{
**	char str[11];
**	char str1[] = "hello";
**
**	ft_strcpy(str,str1);
**	str[5] = '\0';
**	if (argc == 2)
**		printf("ret = %zu\ns1 = %s\n", ft_strlcat(str, argv[1], 4), str);
**	return (0);
**}
*/
