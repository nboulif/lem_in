/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tab_tube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:24:21 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/27 01:36:55 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tube		create_tube(t_node *node1, t_node *node2)
{
	t_tube tube;

	if (!node1 || !node2)
		return ((t_tube){NULL, NULL, 0, 0, 0, 0});
	node1->nb_tube_o++;
	node2->nb_tube_o++;
	tube = (t_tube){node1, node2, 1, 1, BIDIR, 0};
	return (tube);
}

t_node *find_in_lst(t_objectif *obj, char *name, int size)
{
	unsigned long	id;
	t_node_link		*lst_node_lk;
	char			c;

	c = name[size];
	name[size] = 0;
	id = hash((unsigned char*)name) % obj->nb_node;
	lst_node_lk = obj->lst_node_lk[id];
	while (lst_node_lk)
	{
		if (!ft_strcmp(lst_node_lk->node->name, name))
		{
			name[size] = c;
			return (lst_node_lk->node);
		}
		lst_node_lk = lst_node_lk->next;
	}
	return (NULL);
}


t_tube		next_tube(t_objectif *obj, char *str, int *i)
{
	int		x;
	int		l;
	t_tube	tube;

	zap_comm(str, i);
	x = *i;
	l = line_len(str, i) + *i;
	while (x < l)
	{
		if (str[x] == '-')
		{
			if (x == *i)
			{
				*i = l;
				return ((t_tube){NULL, NULL, 0, 0, 0, 0});
			}
			tube = create_tube(
				find_in_lst(obj, str + *i, x - *i),
				find_in_lst(obj, str + x + 1, l - (x + 1)));
			*i = l;
			return (tube);
		}
		x++;
	}
	*i = l;
	return ((t_tube){NULL, NULL, 0, 0, 0, 0});
}

int			make_tab_tube(t_objectif *obj, char *str, int *i)
{
	t_tube	tube;
	int		index;
	int		size;

	index = 0;
	size = obj->nb_node * obj->nb_node;
	if (!(obj->lst_tube = malloc(sizeof(t_tube) * size)))
		return (0);
	while ((tube = next_tube(obj, str, i)).node1)
	{
		if (index > size || !tube.node2)
			return (0);
		if (tube.node1 != tube.node2)
			obj->lst_tube[index++] = tube;
		if (!str[*i])
			break ;
		*i += 1;
	}
	obj->nb_tube = index;
	return (!(!index || (index != size && !ft_realloc((void**)&obj->lst_tube,
		&index, index, sizeof(t_tube)))));
}
