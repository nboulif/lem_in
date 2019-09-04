/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tab_edge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:24:21 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/27 01:36:55 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge		create_edge(t_node *node1, t_node *node2)
{
	t_edge edge;

	if (!node1 || !node2)
		return ((t_edge){NULL, NULL, 0, 0, 0, 0, 0});
	node1->nb_edge_o++;
	node2->nb_edge_o++;
	edge = (t_edge){node1, node2, 1, 1, BIDIR, 0, 0};
	return (edge);
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


t_edge		next_edge(t_objectif *obj, char *str, int *i)
{
	int		x;
	int		l;
	t_edge	edge;

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
				return ((t_edge){NULL, NULL, 0, 0, 0, 0, 0});
			}
			edge = create_edge(
				find_in_lst(obj, str + *i, x - *i),
				find_in_lst(obj, str + x + 1, l - (x + 1)));
			*i = l;
			return (edge);
		}
		x++;
	}
	*i = l;
	return ((t_edge){NULL, NULL, 0, 0, 0, 0, 0});
}

int			make_tab_edge(t_objectif *obj, char *str, int *i)
{
	t_edge	edge;
	int		index;
	int		size;

	index = 0;
	size = obj->nb_node * obj->nb_node;
	if (!(obj->lst_edge = malloc(sizeof(t_edge) * size)))
		return (0);
	while ((edge = next_edge(obj, str, i)).node1)
	{
		if (index > size || !edge.node2)
		{
			return (0);
		}
	if (edge.node1 != edge.node2)
			obj->lst_edge[index++] = edge;
		if (!str[*i])
			break ;
		*i += 1;
	}
	obj->nb_edge = index;
	return (!(!index || (index != size && !ft_realloc((void**)&obj->lst_edge,
		&index, index, sizeof(t_edge)))));
}
