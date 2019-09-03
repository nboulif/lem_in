/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 23:20:53 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/27 00:16:50 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned long	hash(unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 0;
	while ((c = *(str++)))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return (hash);
}

int				line_len(char *str, int *i)
{
	int x;

	x = *i;
	while (str[x] && str[x] != '\n')
		x++;
	return (x - *i);
}

int				ft_min(int a, int b, int c)
{
	if (a < b)
		return (a < c ? a : c);
	return (b < c ? b : c);
}

int				ft_realloc(void **tab, int *size, int new_size, size_t type_size)
{
	char *save;

	if (new_size == *size)
		return (1);
	if (!(save = malloc(new_size * type_size)))
		return (0);
	if (*size)
	{
		ft_memcpy(save, *tab, *size * type_size);
		free(*tab);
	}
	*tab = save;
	if (new_size > *size)
		ft_memset(*tab + *size, 0, (new_size - *size) * type_size);
	*size = new_size;
	return (1);
}

