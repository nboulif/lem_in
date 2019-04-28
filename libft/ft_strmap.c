/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:05:07 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:01:32 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*new_str;
	int		i;
	int		size;

	i = -1;
	new_str = NULL;
	if (s != NULL)
	{
		size = ft_strlen((char*)s) + 1;
		if ((new_str = (char*)malloc(sizeof(char) * size)) == NULL)
			return (NULL);
		while (s[++i])
			new_str[i] = (*f)(*(char*)(s + i));
		new_str[i] = '\0';
	}
	return (new_str);
}
