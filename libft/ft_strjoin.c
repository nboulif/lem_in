/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:33:49 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:01:20 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		size;

	i = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	if ((str = (char*)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	str[size] = '\0';
	while (s1[++i])
		str[i] = (char)s1[i];
	while (*s2)
	{
		str[i] = (char)*s2;
		i++;
		s2++;
	}
	return (str);
}
