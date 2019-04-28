/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:05:07 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:02:08 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	i;
	int				size;

	i = -1;
	newstr = NULL;
	if (s != NULL)
	{
		size = ft_strlen((char*)s) + 1;
		if ((newstr = (char*)malloc(sizeof(char) * size)) == NULL)
			return (NULL);
		while (s[++i])
			newstr[i] = (*f)(i, *(char*)(s + i));
		newstr[i] = '\0';
	}
	return (newstr);
}
