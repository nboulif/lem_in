/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 09:35:28 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:02:59 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *last_c;

	last_c = NULL;
	if (!c)
	{
		if (*s == '\0')
			return ((char*)s);
		else
			return ((char*)(s + ft_strlen(s)));
	}
	while (*s)
	{
		if (*s == (const char)c)
			last_c = s;
		s++;
	}
	return ((char*)last_c);
}
