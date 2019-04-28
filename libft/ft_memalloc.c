/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:34:45 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/06 23:11:17 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	i = -1;
	if (size >= SIZE_MAX)
		return (NULL);
	if (!size || (mem = malloc(sizeof(unsigned char) * size + 1)) == NULL)
		return (NULL);
	while (++i < size)
		*(unsigned char*)(mem + i) = 0;
	return (mem);
}
