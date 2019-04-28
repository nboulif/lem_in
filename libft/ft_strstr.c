/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:23:18 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/06 21:39:03 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int i2;

	i = 0;
	i2 = 0;
	if (!*str && *to_find != *str)
		return (NULL);
	if (*to_find == '\0' || *str == '\0')
		return ((char*)(str));
	while (str[i] != '\0')
	{
		while (str[i + i2] == to_find[i2] && to_find[i2] != '\0')
		{
			i2++;
			if (to_find[i2] == '\0')
				return ((char*)(str + i));
		}
		i++;
		i2 = 0;
	}
	return (NULL);
}
