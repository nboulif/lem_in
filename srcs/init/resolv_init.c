/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:17:16 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 17:48:56 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		create_tab_edge_in_node(t_objectif *obj)
{
	int				i;
	t_node_link		*link;

	i = -1;
	while (++i < obj->nb_node)
	{
		link = obj->lst_node_lk[i];
		while (link)
		{
			if (!(link->node->edge =
				malloc(link->node->nb_edge_o * sizeof(t_edge *))))
				return (0);
			link = link->next;
		}
	}
	return (1);
}

void	rec_init_lst_edge_ord_part_two(t_objectif *obj, t_queue queue, int *k)
{
	int			j;
	t_edge		*edge;
	t_node		*node;

	j = -1;
	while (++j < queue.node[queue.index]->nb_edge_f)
	{
		edge = queue.node[queue.index]->edge[j];
		if (queue.node[queue.index]->id == edge->node1->id)
			node = edge->node2;
		else
			node = edge->node1;
		if (!node->deja_vu_init)
		{
			node->deja_vu_init = 1;
			queue.node[++queue.size_queue] = node;
		}
		if (!edge->deja_vu_init)
		{
			edge->deja_vu_init = 1;
			obj->lst_edge_ord[(*k)++] = edge;
		}
	}
}

int		rec_init_lst_edge_ord(t_objectif *obj)
{
	t_queue		queue;
	int			k;

	obj->lst_edge_ord = (t_edge **)malloc(sizeof(t_edge *) * obj->nb_edge);
	if (!(queue.node = ft_memalloc(sizeof(t_node *) * obj->nb_node)))
		return (0);
	ft_memset(obj->lst_edge_ord, 0, obj->nb_edge);
	ft_memset(queue.node, 0, obj->nb_node);
	queue.node[0] = obj->start_node;
	obj->start_node->deja_vu_init = 1;
	k = 0;
	queue.size_queue = 0;
	queue.index = -1;
	while (++queue.index <= queue.size_queue)
		rec_init_lst_edge_ord_part_two(obj, queue, &k);
	obj->nb_edge_f = k;
	free(queue.node);
	return (1);
}

int		link_node_and_edge(t_objectif *obj)
{
	int		i;
	t_node	*node1;
	t_node	*node2;

	i = -1;
	if (!create_tab_edge_in_node(obj))
		return (0);
	while (++i < obj->nb_edge)
	{
		node1 = obj->lst_edge[i].node1;
		node2 = obj->lst_edge[i].node2;
		if (!is_in_tab_edge(node1->edge, obj->lst_edge + i, node1->nb_edge_f))
		{
			node1->edge[node1->nb_edge_f++] = obj->lst_edge + i;
			node2->edge[node2->nb_edge_f++] = obj->lst_edge + i;
		}
	}
	return (1);
}

int		init_resolv(t_objectif *obj)
{
	if (!link_node_and_edge(obj))
		return (0);
	delete_dead_end(obj);
	rec_init_lst_edge_ord(obj);
	return (1);
}
