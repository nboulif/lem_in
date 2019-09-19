/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 23:20:53 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 17:36:10 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				init_way(t_objectif *obj, t_way *way)
{
	if (!(way->nodes_lk =
		(t_node_link *)malloc(sizeof(t_node_link) * (obj->nb_node + 1))) ||
		!(way->edges_lk =
			(t_edge_link *)malloc(sizeof(t_edge_link) * (obj->nb_node + 1))))
	{
		free(way->nodes_lk);
		return (0);
	}
	return (1);
}

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

int				ft_realloc(void **tab, int *size_av,
		int new_size_ap, size_t type_size)
{
	char			*save;
	unsigned int	size;
	unsigned int	new_size;

	size = *size_av;
	new_size = new_size_ap;
	if (new_size == size)
		return (1);
	if (!(save = malloc(new_size * type_size)))
		return (0);
	if (size)
	{
		ft_memcpy(save, *tab, size * type_size);
		free(*tab);
	}
	*tab = save;
	if (new_size > size)
		ft_memset(*tab + size, 0, (new_size - size) * type_size);
	*size_av = new_size;
	return (1);
}
