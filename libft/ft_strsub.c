/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:26:23 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 15:12:43 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	unsigned int		i;
	char				*troncon;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((troncon = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	troncon[len] = '\0';
	while (i < len)
	{
		troncon[i] = (char)s[start + i];
		i++;
	}
	return (troncon);
}
