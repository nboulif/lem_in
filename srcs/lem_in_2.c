/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 22:42:54 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 17:50:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

int			read_all(char **str, int fd)
{
	int index;
	int size;
	int ret;

	size = SIZE_BUFF + 1;
	if (!(*str = malloc(size * sizeof(char))))
		return (0);
	index = 0;
	while ((ret = read(fd, *str + index, SIZE_BUFF)) > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (ret < SIZE_BUFF)
			return (index);
		if (index + SIZE_BUFF >= size - 1)
			if (!ft_realloc((void **)str, &size, size * 2, sizeof(char)))
				return (0);
	}
	return (index);
}

void		estimate_max_way(t_objectif *obj)
{
	int				i;
	t_node_link		*link;

	obj->max_link = 0;
	i = -1;
	while (++i < obj->nb_node)
	{
		link = obj->lst_node_lk[i];
		while (link)
		{
			if (link->node->nb_edge_f > obj->max_link)
				obj->max_link = link->node->nb_edge_f;
			link = link->next;
		}
	}
	obj->max_way = ft_min(obj->start_node->nb_edge_f, obj->end_node->nb_edge_f,
						obj->max_link);
	obj->max_way = (obj->max_way < obj->nb_ants) ? obj->max_way : obj->nb_ants;
}

t_father	*alloc_t_father(t_objectif *obj, int mode)
{
	static t_father		*tab = NULL;
	static size_t		index = 0;

	if (!mode)
	{
		free(tab);
		return (NULL);
	}
	if (tab == NULL)
	{
		if (!(tab = malloc(sizeof(t_father) * (size_t)(obj->max_way + 1)
		* (size_t)(obj->nb_node + 1))))
			return (NULL);
	}
	index += (obj->max_way + 1);
	return (&tab[index - (obj->max_way + 1)]);
}
