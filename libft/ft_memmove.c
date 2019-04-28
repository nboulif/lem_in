/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:33:32 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 17:08:40 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	int				count;

	if (dest < src)
		return (ft_memcpy(dest, src, n));
	count = -1;
	i = -1;
	while (n-- > 0)
		*(unsigned char*)(dest + n) = *(unsigned char*)(src + n);
	return (dest);
}
/*
**int main()
**{
**	char str1[50] = "une phrase normal de test";
**	char *str2;
**
**	str2 = str1 + 4;
**	printf("str2 = %s\nstr1 = %s\n",str2, str1);
**	ft_memmove(str1, str2, 7);
**	printf("str1 apres move de 7 = %s\n", str1);
**	return (0);
**}
*/
