/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 19:31:49 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/06 21:08:10 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t i2;

	i = 0;
	i2 = 0;
	while (dest[i])
		i++;
	while (i2 < n && src[i2])
		dest[i++] = src[i2++];
	dest[i] = '\0';
	return (dest);
}
