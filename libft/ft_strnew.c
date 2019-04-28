/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:49:56 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:04:26 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = -1;
	if ((str = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	while (++i < size + 1)
		str[i] = '\0';
	return (str);
}
